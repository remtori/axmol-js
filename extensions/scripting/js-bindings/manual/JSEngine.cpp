#include "JSEngine.h"

#include "JSConversions.h"

#include <libplatform/libplatform.h>
#include <v8.h>

#include "axmol/base/Object.h"
#include "axmol/base/Macros.h"
#include "axmol/base/EventDispatcher.h"
#include "axmol/base/Director.h"
#include "axmol/platform/FileUtils.h"

#include "generated/js_bootstrap_core.h"
#include "js-bindings/manual/js_bootstrap_bindings.h"
#include "js-bindings/manual/js_module_register.h"

#include "v8pp/class.hpp"
#include "v8pp/object.hpp"

namespace
{

const char* SCHEDULE_KEY = "JSEngine::update";

}  // namespace

namespace ax
{
static std::once_flag _initV8Platform;

JSEngine* JSEngine::fromIsolate(v8::Isolate* isolate)
{
    JSEngine* engine = static_cast<JSEngine*>(isolate->GetData(0));
    AXASSERT(engine, "JSEngine::fromIsolate() - no JSEngine found");
    return engine;
}

JSEngine::JSEngine() {}

JSEngine::~JSEngine()
{
    AXASSERT(_isolate == nullptr, "cleanup() must been called before we destruct JSEngine");
}

void JSEngine::cleanup()
{
    if (_isolate == nullptr)
        return;

    v8::Isolate* finalIsolate = _isolate;
    _isolate                  = nullptr;

    ax::Director* director               = ax::Director::getInstance();
    ax::EventDispatcher* eventDispatcher = director->getEventDispatcher();
    if (_directorResetListener)
    {
        eventDispatcher->removeEventListener(_directorResetListener);
        _directorResetListener = nullptr;
    }

    ax::Scheduler* scheduler = director->getScheduler();
    if (scheduler)
    {
        scheduler->unschedule(SCHEDULE_KEY, this);
    }

    finalIsolate->SetData(0, nullptr);

    _timers.clear();
    v8pp::cleanup(finalIsolate);

    _eventLoopTickFn.Reset();
    _callsitePrototype.Reset();
    _globalObject.Reset();
    _context.Reset();

    _isolateData.reset();

    finalIsolate->Exit();
    finalIsolate->Dispose();
}

bool JSEngine::init()
{
    std::call_once(_initV8Platform, []() {
        auto platform = v8::platform::NewDefaultPlatform(1);
        v8::V8::InitializePlatform(platform.release());

        std::string flags;
        // NOTICE: spaces are required between flags
        flags.append(" --expose-gc-as=__jsb_gc__");

        // for bytecode support
        flags.append(" --no-flush-bytecode --no-lazy");

        // v8 trace gc
        // flags.append(" --trace-gc");

        // NOTICE: should be remove flag --no-turbo-escape after upgrade v8 to 10.x
        // https://github.com/cocos/cocos-engine/issues/13342
        flags.append(" --no-turbo-escape");

#if AX_TARGET_PLATFORM == AX_PLATFORM_IOS || AX_TARGET_PLATFORM == AX_PLATFORM_OPENHARMONY
        flags.append(" --jitless");
#endif

        if (!flags.empty())
        {
            v8::V8::SetFlagsFromString(flags.c_str(), static_cast<int>(flags.length()));
        }

        v8::V8::Initialize();
    });

    static v8::ArrayBuffer::Allocator* arrayBufferAllocator{nullptr};
    if (arrayBufferAllocator == nullptr)
    {
        arrayBufferAllocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    }

    v8::Isolate::CreateParams createParams;
    createParams.array_buffer_allocator = arrayBufferAllocator;
    createParams.fatal_error_callback   = [](const char* location, const char* message) {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        if (isolate->IsExecutionTerminating())
        {
            isolate->CancelTerminateExecution();
        }

        AXLOGE("[JS] fatal error: {} {}", location, message);
    };
    createParams.oom_error_callback = [](const char* location, const v8::OOMDetails& details) {
        AXLOGE("[JS] oom error: {} {}", location, details.detail);
    };

    _isolate = v8::Isolate::New(createParams);
    _isolate->Enter();

    v8::HandleScope handleScope(_isolate);

    /// Must be same index as in `JSEngine::fromIsolate`
    _isolate->SetData(0, this);
    _isolate->SetCaptureStackTraceForUncaughtExceptions(true, 10);
    // _isolate->SetPrepareStackTraceCallback(prepareStackTrace);
    _isolate->AddMessageListener([](v8::Local<v8::Message> message, v8::Local<v8::Value> data) {
        reportException(v8::Isolate::GetCurrent(), message, data);
    });

    _context.Reset(_isolate, v8::Context::New(_isolate));
    v8::Local<v8::Context> context = _context.Get(_isolate);
    context->Enter();

    v8::Context::Scope contextScope(context);
    _globalObject.Reset(_isolate, context->Global());
    _isolateData.emplace(_isolate);

    js_bootstrap_bindings(_isolate, context);
    evalWithOrigin("core:00_primordials.js", generated::_00_primordials);
    evalWithOrigin("core:00_infra.js", generated::_00_infra);
    evalWithOrigin("core:01_core.js", generated::_01_core);

    v8::Local<v8::Function> eventLoopTickFn;
    if (!v8pp::get_option(_isolate, _globalObject.Get(_isolate), "__bootstrap.core.eventLoopTick", eventLoopTickFn))
    {
        AXASSERT(false, "JSEngine::init() - eventLoopTick function not found");
        return false;
    }
    _eventLoopTickFn.Reset(_isolate, eventLoopTickFn);

    JsRegistry registry(_isolate);
    js_module_register(registry);

    v8::Local<v8::Object> bindings = registry.getAllAsObject();
    _globalObject.Get(_isolate)->Set(context, ext().__bindings_string(), bindings).ToChecked();

    evalWithOrigin("core:02_console.js", generated::_02_console);
    evalWithOrigin("core:02_axmol_ops.js", generated::_02_axmol_ops);
    evalWithOrigin("core:02_path.js", generated::_02_path);
    evalWithOrigin("core:02_timers.js", generated::_02_timers);
    evalWithOrigin("core:03_require.js", generated::_03_require);

    AXLOGI("[JS] v8 version: {}.{}.{}.{}", V8_MAJOR_VERSION, V8_MINOR_VERSION, V8_BUILD_NUMBER, V8_PATCH_LEVEL);

    ax::Director* director = ax::Director::getInstance();

    ax::Scheduler* scheduler = director->getScheduler();
    scheduler->schedule(std::bind(&JSEngine::update, this, std::placeholders::_1), this, 0.0f, false, SCHEDULE_KEY);

    ax::EventDispatcher* eventDispatcher = director->getEventDispatcher();
    _directorResetListener               = eventDispatcher->addCustomEventListener(ax::Director::EVENT_RESET,
                                                                                   [this](ax::EventCustom*) { this->cleanup(); });

    return true;
}

void JSEngine::evalWithOrigin(std::string_view originStr, std::string_view codeStr)
{
    AXLOGI("[JS] evaluating: {}", originStr);

    v8::HandleScope scope(_isolate);

    v8::Local<v8::Context> context = _context.Get(_isolate);
    v8::Context::Scope contextScope(context);
    v8::TryCatch tryCatch(_isolate);

    v8::ScriptOrigin origin(_isolate, v8pp::to_v8(_isolate, originStr));
    v8::Local<v8::String> source = v8pp::to_v8(_isolate, codeStr);

    v8::Local<v8::Script> script;
    if (!v8::Script::Compile(context, source, &origin).ToLocal(&script))
    {
        AXASSERT(tryCatch.HasCaught(), "JSEngine::evalWithOrigin() - failed to catch compile script error");
        reportException(_isolate, tryCatch);
        return;
    }

    std::string_view previousEvalOrigin = _currentEvalOrigin;
    _currentEvalOrigin                  = originStr;

    v8::Local<v8::Value> result;
    if (!script->Run(context).ToLocal(&result))
    {
        AXASSERT(tryCatch.HasCaught(), "JSEngine::evalWithOrigin() - failed to catch run script error");
        reportException(_isolate, tryCatch);

        _currentEvalOrigin = previousEvalOrigin;
        return;
    }

    AXASSERT(!tryCatch.HasCaught(), "JSEngine::evalWithOrigin() - failed to catch script error");
    _currentEvalOrigin = previousEvalOrigin;
}

int JSEngine::executeString(const char* codes)
{
    evalWithOrigin("<anonymous>", std::string_view(codes));
    return 1;
}

int JSEngine::executeScriptFile(const char* filename)
{
    AXASSERT(filename, "JSEngine::executeScriptFile() - invalid filename");

    std::string filePath = FileUtils::getInstance()->fullPathForFilename(filename);
    Data data            = FileUtils::getInstance()->getDataFromFile(filePath);
    if (data.isNull())
    {
        return 0;
    }

    evalWithOrigin(filePath, std::string_view(reinterpret_cast<char*>(data.getBytes()), data.getSize()));
    return 1;
}

int JSEngine::executeGlobalFunction(const char* functionName)
{
    v8::HandleScope scope(_isolate);
    v8::Context::Scope contextScope(_context.Get(_isolate));
    v8::TryCatch tryCatch(_isolate);

    v8::Local<v8::String> v8FunctionName = v8::String::NewFromUtf8(_isolate, functionName).ToLocalChecked();

    v8::Local<v8::Context> context = _context.Get(_isolate);
    v8::Local<v8::Value> func;
    if (!context->Global()->Get(context, v8FunctionName).ToLocal(&func))
    {
        return 0;
    }

    if (!func->IsFunction())
    {
        return 0;
    }

    v8::Local<v8::Function> function = v8::Local<v8::Function>::Cast(func);
    v8::Local<v8::Value> result;
    if (!function->Call(context, v8::Undefined(_isolate), 0, nullptr).ToLocal(&result))
    {
        AXASSERT(tryCatch.HasCaught(), "JSEngine::executeGlobalFunction() - failed to catch run function error");
        reportException(_isolate, tryCatch);

        return 0;
    }

    return 1;
}

void JSEngine::update(float)
{
    v8::HandleScope scope(_isolate);
    v8::Local<v8::Context> context = _context.Get(_isolate);
    v8::Context::Scope contextScope(context);

    auto callbacks              = _timers.pollTimers(_isolate);
    v8::Local<v8::Array> timers = v8::Array::New(_isolate, callbacks.size() * 3);
    for (size_t i = 0; i < callbacks.size(); i++)
    {
        auto& data = callbacks[i];
        (void)timers->Set(context, i * 3 + 0, v8::Uint32::New(_isolate, std::get<0>(data))).ToChecked();
        (void)timers->Set(context, i * 3 + 1, v8::Number::New(_isolate, std::get<1>(data))).ToChecked();
        (void)timers->Set(context, i * 3 + 2, std::get<2>(data)).ToChecked();
    }

    v8::TryCatch tryCatch(_isolate);

    v8::Local<v8::Value> args[3] = {
        v8::Array::New(_isolate, 0),
        v8::Undefined(_isolate),
        timers,
    };

    v8::Local<v8::Function> eventLoopTickFn = _eventLoopTickFn.Get(_isolate);
    if (eventLoopTickFn->Call(context, v8::Undefined(_isolate), sizeof(args) / sizeof(args[0]), args).IsEmpty())
    {
        AXASSERT(tryCatch.HasCaught(), "JSEngine::update() - failed to catch eventLoopTick function error");
        reportException(_isolate, tryCatch);
    }
}

int JSEngine::sendEvent(const ScriptEvent& evt)
{
    if (_isolate == nullptr)
        return 0;

    switch (evt.type)
    {
    case kNodeEvent:
        return handleNodeEvent(*reinterpret_cast<BasicScriptData*>(evt.data));
    default:;
    }

    return 0;
}

int JSEngine::handleNodeEvent(const BasicScriptData& data)
{
    auto& registry = v8pp::detail::classes::find(_isolate, v8pp::detail::type_id<ax::Node>());

    ax::Node* obj = reinterpret_cast<ax::Node*>(data.nativeObject);
    int action    = *reinterpret_cast<int*>(data.value);

    v8::HandleScope scope(_isolate);
    v8::Local<v8::Context> context = _context.Get(_isolate);
    v8::Context::Scope contextScope(context);

    auto v8Object = registry.find_v8_object(obj);
    if (v8Object.IsEmpty())
    {
        return 0;
    }

    v8::Local<v8::Value> dispatchNodeEvent;
    if (v8Object->Get(context, ext().dispatch_node_event_private_symbol()).ToLocal(&dispatchNodeEvent) &&
        dispatchNodeEvent->IsFunction())
    {
        v8::Local<v8::Function> dispatchNodeEventFn = v8::Local<v8::Function>::Cast(dispatchNodeEvent);

        v8::TryCatch tryCatch(_isolate);
        v8::Local<v8::Value> args[1] = {v8::Int32::New(_isolate, action)};
        if (dispatchNodeEventFn->Call(context, v8Object, 1, args).IsEmpty())
        {
            AXASSERT(tryCatch.HasCaught(),
                     "JSEngine::handleNodeEvent() - failed to catch dispatchNodeEvent function error");
            reportException(_isolate, tryCatch);
        }
    }

    return 0;
}

bool JSEngine::handleAssert(const char* msg)
{
    return false;
}

bool JSEngine::parseConfig(ConfigType type, std::string_view str)
{
    return false;
}

void JSEngine::rootObject(Object* obj) {}

void JSEngine::unrootObject(Object* obj) {}

void JSEngine::removeObjectProxy(Object* obj) {}

void JSEngine::removeScriptObjectByObject(Object* obj)
{
    if (_isolate == nullptr)
        return;

    try
    {
        v8pp::class_<ax::Object>::destroy_object(_isolate, obj);
    }
    catch (const std::exception& ex)
    {
        AXLOGE("JSEngine::removeScriptObjectByObject() - failed to unreference external object: {}", ex.what());
    }
}

void JSEngine::garbageCollect() {}

void JSEngine::reportException(v8::Isolate* isolate, const v8::TryCatch& tryCatch)
{
    AXASSERT(tryCatch.HasCaught(), "JSEngine::reportException() - tryCatch has no exception");

    if (isolate->IsExecutionTerminating())
    {
        AXLOGE("[JS Scripting] Got Execution Termination Exception\n");
    }
    else
    {
        reportException(isolate, tryCatch.Message(), tryCatch.Exception());
    }
}

void JSEngine::reportException(v8::Isolate* isolate, v8::Local<v8::Message> message, v8::Local<v8::Value> exceptionObj)
{
    v8::HandleScope scope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();

    bool enterContext = context.IsEmpty();
    if (enterContext)
    {
        return;
    }

    // Converts a V8 value to a C string.
    auto ToCString = [](const v8::String::Utf8Value& value) { return *value ? *value : "<string conversion failed>"; };

    // Safely convert exception to string
    v8::String::Utf8Value exception(isolate, exceptionObj);
    const char* exceptionString = ToCString(exception);

    if (message.IsEmpty())
    {
        // V8 didn't provide any extra information about this error; just
        // print the exception.
        printf("%s\n", exceptionString);
    }
    else if (message->GetScriptOrigin().Options().IsWasm())
    {
        // Print wasm-function[(function index)]:(offset): (message).
        int function_index         = message->GetWasmFunctionIndex();
        v8::Maybe<int> columnMaybe = message->GetStartColumn(context);
        int offset                 = columnMaybe.IsJust() ? columnMaybe.FromJust() : 0;
        printf("wasm-function[%d]:0x%x: %s\n", function_index, offset, exceptionString);
    }
    else
    {
        // Print (filename):(line number): (message).
        v8::String::Utf8Value filename(isolate, message->GetScriptOrigin().ResourceName());
        const char* filenameString = ToCString(filename);
        int linenum                = message->GetLineNumber(context).FromMaybe(-1);
        printf("%s:%i: %s\n", filenameString, linenum, exceptionString);

        v8::Local<v8::String> sourceline;
        if (message->GetSourceLine(context).ToLocal(&sourceline))
        {
            // Print line of source code.
            v8::String::Utf8Value sourcelinevalue(isolate, sourceline);
            const char* sourcelineString = ToCString(sourcelinevalue);
            printf("%s\n", sourcelineString);

            // Print wavy underline (GetUnderline is deprecated).
            v8::Maybe<int> startMaybe = message->GetStartColumn(context);
            v8::Maybe<int> endMaybe   = message->GetEndColumn(context);

            if (startMaybe.IsJust() && endMaybe.IsJust())
            {
                int start = startMaybe.FromJust();
                int end   = endMaybe.FromJust();

                for (int i = 0; i < start; i++)
                {
                    printf(" ");
                }
                for (int i = start; i < end; i++)
                {
                    printf("^");
                }
                printf("\n");
            }
        }
    }

    // Try to get stack trace safely
    v8::Local<v8::Value> stacktraceString;
    if (v8::TryCatch::StackTrace(context, exceptionObj).ToLocal(&stacktraceString) && stacktraceString->IsString())
    {
        v8::String::Utf8Value stacktrace(isolate, stacktraceString.As<v8::String>());
        printf("%s\n", ToCString(stacktrace));
    }

    printf("\n");
    fflush(stdout);
    if (enterContext)
        context->Exit();
}
}  // namespace ax
