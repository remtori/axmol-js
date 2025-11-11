#include "js_bootstrap_bindings.h"

#include <v8.h>

#include "v8pp/call_from_v8.hpp"
#include "v8pp/convert.hpp"
#include "v8pp/module.hpp"
#include "v8pp/ptr_traits.hpp"

#include "JSEngine.h"
#include "JSConversions.h"

#include "js_storage.h"

extern void js_bind_ops_builtin_v8(v8pp::module& mod);
extern void js_bind_ops_builtin_types(v8pp::module& mod);

namespace
{

void bind_ops(v8pp::module& mod)
{
    js_bind_ops_builtin_v8(mod);
    js_bind_ops_builtin_types(mod);
    js_bind_ops_storage(mod);

    mod.function("op_timer_queue",
                 [](v8::Isolate* isolate, uint32_t depth, bool repeat, double timeoutMs,
                    v8::Local<v8::Value> data) -> ax::JsTimers::TimerId {
        v8::HandleScope scope(isolate);

        if (!data->IsFunction())
        {
            v8pp::throw_type_error(isolate, "Invalid arguments");
            return 0;
        }

        ax::JSEngine* jsEngine = ax::JSEngine::fromIsolate(isolate);
        auto timerData = std::make_tuple(depth, v8::Global<v8::Function>(isolate, v8::Local<v8::Function>::Cast(data)));
        if (repeat)
        {
            return jsEngine->jsTimers().queueTimerRepeat(timeoutMs, std::move(timerData));
        }
        else
        {
            return jsEngine->jsTimers().queueTimer(timeoutMs, std::move(timerData));
        }
    });
    mod.function("op_timer_cancel", [](v8::Isolate* isolate, ax::JsTimers::TimerId id) {
        v8::HandleScope scope(isolate);
        ax::JSEngine* jsEngine = ax::JSEngine::fromIsolate(isolate);
        jsEngine->jsTimers().cancelTimer(id);
    });

    mod.function("op_register_conversion_prototype", [](v8::Isolate* isolate, v8::Local<v8::Value> clazzValue) {
        v8::HandleScope scope(isolate);
        v8::Local<v8::Context> context = isolate->GetCurrentContext();

        if (!clazzValue->IsObject())
        {
            v8pp::throw_type_error(isolate, "Class is not an object");
            return;
        }

        v8::Local<v8::Object> clazz = clazzValue.As<v8::Object>();
        auto& ext                   = ax::JSEngine::fromIsolate(isolate)->mutable_ext();

        std::string clazzName;
        if (!object_get(isolate, clazz, ext.name_string(), clazzName))
        {
            v8pp::throw_type_error(isolate, "Failed to get class name");
            return;
        }

        v8::Local<v8::Value> prototype;
        if (!clazz->Get(context, ext.prototype()).ToLocal(&prototype))
        {
            v8pp::throw_type_error(isolate, "Failed to get prototype");
            return;
        }

        if (!prototype->IsObject())
        {
            v8pp::throw_type_error(isolate, "Prototype is not an object");
            return;
        }

        ext.registerConversionPrototype(clazzName, prototype.As<v8::Object>());
    });

    mod.function("op_cocos_require", [](v8::Isolate* isolate, std::string path) {
        ax::JSEngine::fromIsolate(isolate)->executeScriptFile(path.c_str());
    });
}

}  // namespace

void js_bootstrap_bindings(v8::Isolate* isolate, v8::Local<v8::Context> context)
{
    v8::HandleScope scope(isolate);
    auto& ext = ax::JSEngine::fromIsolate(isolate)->ext();

    v8::Local<v8::Object> global = context->Global();

    // Bootstrap namespace already exists, exit early
    if (global->Get(context, ext.__bootstrap_string()).IsEmpty())
    {
        return;
    }

    v8::Local<v8::Object> bootstrap = v8::Object::New(isolate);

    v8pp::module ops_module(isolate);
    bind_ops(ops_module);
    bootstrap->Set(context, ext.ops_string(), ops_module.new_instance()).Check();

    global->Set(context, ext.__bootstrap_string(), bootstrap).Check();
}
