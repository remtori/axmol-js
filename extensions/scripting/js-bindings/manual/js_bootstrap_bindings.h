#pragma once

#include <v8.h>
#include <v8-fast-api-calls.h>
#include <v8pp/module.hpp>

void js_bootstrap_bindings(v8::Isolate* isolate, v8::Local<v8::Context> context);

template <typename Func>
void fast_call(v8pp::module& mod, std::string_view name, Func* func)
{
    v8::Isolate* isolate = mod.isolate();
    v8::HandleScope scope(isolate);

    auto slowFunc = [](const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::Isolate* isolate = args.GetIsolate();
        v8::HandleScope scope(isolate);

        Func* func = reinterpret_cast<Func*>(args.Data().As<v8::External>()->Value());
        auto ret   = v8pp::detail::call_from_v8<v8pp::object_ptr_traits>(func, args);
        args.GetReturnValue().Set(v8pp::to_v8(isolate, ret));
    };
    v8::CFunction cFunc = v8::CFunction::Make(func);

    v8::Local<v8::FunctionTemplate> funcTemplate = v8::FunctionTemplate::New(
        isolate, slowFunc, v8::External::New(isolate, reinterpret_cast<void*>(func)), v8::Local<v8::Signature>(), 1,
        v8::ConstructorBehavior::kThrow, v8::SideEffectType::kHasNoSideEffect, &cFunc);

    mod.value(name, funcTemplate);
}
