#include "js_isolate_data.h"

#include "JSEngine.h"

#include <stdexcept>

namespace ax
{

/**
 * Life cycle of a JS callback function
 * - IsolateData hold a weak reference to `JSCallbackObject`
 * - The user/consumer of `JSCallbackObject`, mostly in the form of std::function will hold strong reference to it
 * - On destruction of `JSCallbackObject`, it removes itself from IsolateData's map
 */
ax::RefPtr<JSCallbackObject> JSCallbackObject::get_or_create(v8::Isolate* isolate, v8::Local<v8::Function> func)
{
    if (func.IsEmpty() || !func->IsFunction())
        throw std::runtime_error("jsval is not a function");

    v8::HandleScope scope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();

    ax::JSEngine* engine = ax::JSEngine::fromIsolate(isolate);
    auto& callbackMap    = engine->mutable_ext().callbackMap();

    int hash = func->GetIdentityHash();

    auto& callbacks = callbackMap[hash];
    for (auto* cb : callbacks)
    {
        if (cb->_callback == func)
        {
            return ax::RefPtr(cb, axstd::retain_object);
        }
    }

    ax::RefPtr<JSCallbackObject> ret(new JSCallbackObject(isolate, v8::Global<v8::Function>(isolate, func)));
    callbacks.insert(ret.get());
    return ret;
}

JSCallbackObject::JSCallbackObject(v8::Isolate* isolate, v8::Global<v8::Function> func)
    : ax::Object()
    , _isolate(isolate)
    , _callback(std::move(func))
{}

JSCallbackObject::~JSCallbackObject()
{
    ax::JSEngine* engine = ax::JSEngine::fromIsolate(_isolate);
    auto& callbackMap    = engine->mutable_ext().callbackMap();

    int hash = _callback.Get(_isolate)->GetIdentityHash();

    auto it = callbackMap.find(hash);
    if (it != callbackMap.end())
    {
        it->second.erase(this);
        if (it->second.empty())
        {
            callbackMap.erase(it);
        }
    }
}

v8::MaybeLocal<v8::Value> JSCallbackObject::call_v8(int argc, v8::Local<v8::Value> argv[])
{
    v8::Isolate* isolate = _isolate;
    if (_callback.IsEmpty())
        return {};

    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Context::Scope contextScope(context);

    v8::TryCatch tryCatch(isolate);
    v8::Local<v8::Value> target = v8::Null(isolate);
    v8::Local<v8::Function> localFunc = _callback.Get(isolate);

    v8::Local<v8::Value> result;
    (void)localFunc->Call(context, target, argc, argv).ToLocal(&result);
    if (tryCatch.HasCaught())
    {
        ax::JSEngine::reportException(isolate, tryCatch);
        return {};
    }

    return result;
}

IsolateData::IsolateData(v8::Isolate* isolate) : _isolate(isolate)
{
    create_properties();
}

IsolateData::~IsolateData() {}

void IsolateData::create_properties()
{
    // Create string and private symbol properties as internalized one byte
    // strings after the platform is properly initialized.
    //
    // Internalized because it makes property lookups a little faster and
    // because the string is created in the old space straight away.  It's going
    // to end up in the old space sooner or later anyway but now it doesn't go
    // through v8::Eternal's new space handling first.
    //
    // One byte because our strings are ASCII and we can safely skip V8's UTF-8
    // decoding step.

    v8::Isolate::Scope isolate_scope(_isolate);
    v8::HandleScope handle_scope(_isolate);

#define V(PropertyName, StringValue)                                                                                  \
    _##PropertyName.Set(                                                                                              \
        _isolate, v8::Symbol::For(                                                                                    \
                      _isolate, v8::String::NewFromOneByte(_isolate, reinterpret_cast<const uint8_t*>(StringValue),   \
                                                           v8::NewStringType::kInternalized, sizeof(StringValue) - 1) \
                                    .ToLocalChecked()));
    PER_ISOLATE_SYMBOL_PROPERTIES(V)
#undef V

#define V(PropertyName, StringValue)                                                                          \
    _##PropertyName.Set(_isolate,                                                                             \
                        v8::String::NewFromOneByte(_isolate, reinterpret_cast<const uint8_t*>(StringValue),   \
                                                   v8::NewStringType::kInternalized, sizeof(StringValue) - 1) \
                            .ToLocalChecked());
    PER_ISOLATE_STRING_PROPERTIES(V)
#undef V
}

void IsolateData::registerConversionPrototype(std::string_view name, v8::Local<v8::Object> prototype)
{
#define V(PrototypeName)                                   \
    if (name == #PrototypeName)                            \
    {                                                      \
        _proto_##PrototypeName.Reset(_isolate, prototype); \
        return;                                            \
    }
    PER_ISOLATE_CLASS_PROTOTYPE(V)
#undef V

    std::string message = "Register conversion prototype for unknown class: ";
    message += name;

    throw std::runtime_error(message);
}

}  // namespace ax
