#include "js_bootstrap_bindings.h"

#include "axmol/base/Macros.h"
#include "axmol/platform/PlatformConfig.h"

#include "JSEngine.h"

namespace
{

struct EvalContextError
{
    v8::Local<v8::Value> thrown;
    bool isNativeError;
    bool isCompileError;

    v8::Local<v8::Value> to_v8(v8::Isolate* isolate) const
    {
        v8::Local<v8::Context> context = isolate->GetCurrentContext();

        v8::Local<v8::Array> ret = v8::Array::New(isolate, 3);
        ret->Set(context, 0, thrown).Check();
        ret->Set(context, 1, v8::Boolean::New(isolate, isNativeError)).Check();
        ret->Set(context, 2, v8::Boolean::New(isolate, isCompileError)).Check();
        return ret;
    }
};

bool is_instance_of_error(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    if (!value->IsObject())
        return false;

    v8::Local<v8::String> message = v8::String::Empty(isolate);
    v8::Local<v8::Value> errorPrototype =
        v8::Exception::Error(message)->ToObject(context).ToLocalChecked()->GetPrototypeV2();

    v8::Local<v8::Value> maybePrototype = value->ToObject(context).ToLocalChecked()->GetPrototypeV2();
    while (!maybePrototype.IsEmpty())
    {
        if (!maybePrototype->IsObject())
        {
            return false;
        }

        if (maybePrototype->StrictEquals(errorPrototype))
        {
            return true;
        }

        maybePrototype = maybePrototype.As<v8::Object>()->GetPrototypeV2();
    }

    return false;
}

void op_call_console(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (args.Length() < 2 || !args[0]->IsFunction() || !args[1]->IsFunction())
    {
        v8pp::throw_type_error(args.GetIsolate(), "Invalid arguments");
        return;
    }

    v8::HandleScope scope(args.GetIsolate());
    v8::Local<v8::Context> context = args.GetIsolate()->GetCurrentContext();

    std::vector<v8::Local<v8::Value>> callArgs;
    callArgs.reserve(args.Length() - 2);
    for (size_t i = 2; i < args.Length(); ++i)
    {
        callArgs.push_back(args[i]);
    }

    v8::Local<v8::Value> receiver                  = args.This();
    v8::Local<v8::Function> inspectorConsoleMethod = v8::Local<v8::Function>::Cast(args[0]);
    v8::Local<v8::Function> bootstrapConsoleMethod = v8::Local<v8::Function>::Cast(args[1]);

    (void)inspectorConsoleMethod->Call(context, receiver, callArgs.size(), callArgs.data());
    (void)bootstrapConsoleMethod->Call(context, receiver, callArgs.size(), callArgs.data());
}

}  // namespace

static v8::Local<v8::Value> op_serialize(v8::Isolate* isolate,
                                         v8::Local<v8::Value> value,
                                         v8::Local<v8::Value> hostObjects,
                                         v8::Local<v8::Value> transferredArrayBuffers,
                                         bool forStorage,
                                         v8::Local<v8::Value> errorCallback);

static v8::Local<v8::Value> op_deserialize(v8::Isolate* isolate,
                                           v8::Local<v8::Value> buffer,
                                           v8::Local<v8::Value> hostObjects,
                                           v8::Local<v8::Value> transferredArrayBuffers,
                                           bool forStorage);

void js_bind_ops_builtin_v8(v8pp::module& mod)
{
    mod.function("op_print", [](std::string str, bool isErr) {
        auto stream = isErr ? stderr : stdout;
        fprintf(stream, "%s", str.data());
        fflush(stream);
    });
    mod.function("op_is_windows", []() {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32 || AX_TARGET_PLATFORM == AX_PLATFORM_WINUWP)
        return true;
#else
        return false;
#endif
    });
    mod.function("op_call_console", op_call_console);
    mod.function("op_get_extras_binding_object", [](const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::Isolate* isolate = args.GetIsolate();
        v8::HandleScope scope(isolate);
        v8::Local<v8::Context> context = isolate->GetCurrentContext();
        args.GetReturnValue().Set(context->GetExtrasBindingObject());
    });
    mod.function("op_memory_usage", [](const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::Isolate* isolate = args.GetIsolate();
        auto& ext            = ax::JSEngine::fromIsolate(isolate)->ext();
        v8::HandleScope scope(isolate);
        v8::HeapStatistics heap_stats;
        isolate->GetHeapStatistics(&heap_stats);

        v8::Local<v8::Name> names[] = {
            ext.physical_total(),
            ext.heap_total(),
            ext.heap_used(),
            ext.external(),
        };
        v8::Local<v8::Value> values[] = {
            v8pp::to_v8(isolate, heap_stats.total_physical_size()),
            v8pp::to_v8(isolate, heap_stats.total_heap_size()),
            v8pp::to_v8(isolate, heap_stats.used_heap_size()),
            v8pp::to_v8(isolate, heap_stats.external_memory()),
        };

        args.GetReturnValue().Set(
            v8::Object::New(isolate, v8::Null(isolate), names, values, sizeof(names) / sizeof(names[0])));
    });
    mod.function("op_get_promise_details",
                 [](v8::Isolate* isolate, v8::Local<v8::Value> value) -> v8::Local<v8::Value> {
        if (!value->IsPromise())
        {
            v8pp::throw_type_error(isolate, "Invalid arguments");
            return v8::Undefined(isolate);
        }

        v8::Local<v8::Promise> promise = v8::Local<v8::Promise>::Cast(value);

        v8::Local<v8::Integer> state;
        v8::Local<v8::Value> result = v8::Null(isolate);
        switch (promise->State())
        {
        case v8::Promise::PromiseState::kPending:
            state = v8::Integer::New(isolate, 0);
            break;
        case v8::Promise::PromiseState::kFulfilled:
            state  = v8::Integer::New(isolate, 1);
            result = promise->Result();
            break;
        case v8::Promise::PromiseState::kRejected:
            state  = v8::Integer::New(isolate, 2);
            result = promise->Result();
            break;
        }

        v8::Local<v8::Array> out = v8::Array::New(isolate, 2);
        out->Set(isolate->GetCurrentContext(), 0, state).Check();
        out->Set(isolate->GetCurrentContext(), 1, result).Check();
        return out;
    });
    mod.function("op_get_proxy_details", [](v8::Isolate* isolate, v8::Local<v8::Value> value) -> v8::Local<v8::Value> {
        if (!value->IsProxy())
        {
            return v8::Null(isolate);
        }

        v8::Local<v8::Proxy> proxy = v8::Local<v8::Proxy>::Cast(value);

        v8::Local<v8::Array> out = v8::Array::New(isolate, 2);
        out->Set(isolate->GetCurrentContext(), 0, proxy->GetTarget()).Check();
        out->Set(isolate->GetCurrentContext(), 1, proxy->GetHandler()).Check();
        return out;
    });
    mod.function("op_get_constructor_name",
                 [](v8::Isolate* isolate, v8::Local<v8::Value> value) -> v8::Local<v8::Value> {
        if (!value->IsObject())
        {
            return v8::Null(isolate);
        }

        return value.As<v8::Object>()->GetConstructorName();
    });
    mod.function("op_get_non_index_property_names",
                 [](v8::Isolate* isolate, v8::Local<v8::Value> value, uint32_t filter) -> v8::Local<v8::Value> {
        if (!value->IsObject())
        {
            return v8::Null(isolate);
        }

        v8::Local<v8::Object> obj = value.As<v8::Object>();

        v8::Local<v8::Array> names;
        if (obj->GetPropertyNames(isolate->GetCurrentContext(), v8::KeyCollectionMode::kOwnOnly,
                                  v8::PropertyFilter(filter), v8::IndexFilter::kSkipIndices)
                .ToLocal(&names))
        {
            return names;
        }

        return v8::Null(isolate);
    });
    mod.function("op_preview_entries",
                 [](v8::Isolate* isolate, v8::Local<v8::Object> object, bool slowPath) -> v8::Local<v8::Value> {
        v8::HandleScope scope(isolate);

        bool isKeyValue                        = false;
        v8::MaybeLocal<v8::Array> maybeEntries = object->PreviewEntries(&isKeyValue);
        if (maybeEntries.IsEmpty())
        {
            return v8::Undefined(isolate);
        }

        v8::Local<v8::Array> entries = maybeEntries.ToLocalChecked();
        if (!slowPath)
        {
            return entries;
        }

        v8::Local<v8::Value> ret[2] = {entries, v8::Boolean::New(isolate, isKeyValue)};
        return v8::Array::New(isolate, ret, 2);
    });
    mod.function("op_run_microtasks", [](v8::Isolate* isolate) -> void { isolate->PerformMicrotaskCheckpoint(); });
    mod.function("op_eval_origin", [](v8::Isolate* isolate) -> std::string_view {
        return ax::JSEngine::fromIsolate(isolate)->currentEvalOrigin();
    });
    mod.function("op_eval_context", [](const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::Isolate* isolate = args.GetIsolate();
        v8::HandleScope scope(isolate);

        v8::Local<v8::Context> context = isolate->GetCurrentContext();
        v8::Context::Scope contextScope(context);
        v8::TryCatch tryCatch(isolate);

        if (args.Length() < 2 || !args[1]->IsString())
        {
            v8pp::throw_type_error(isolate, "Invalid arguments");
            return;
        }

        // Already checked above
        v8::Local<v8::String> specifier = args[1].As<v8::String>();

        v8::Local<v8::String> source;
        if (!args[0]->ToString(context).ToLocal(&source))
        {
            v8pp::throw_type_error(isolate, "Invalid arguments, source cant be converted to string");
            return;
        }

        v8::Local<v8::Data> hostDefinedOptions;
        if (args.Length() == 3)
        {
            if (!args[2]->IsArray())
            {
                v8pp::throw_type_error(isolate, "Invalid arguments, host defined options must be an primitive array");
                return;
            }

            v8::Local<v8::Array> in           = v8::Local<v8::Array>::Cast(args[2]);
            v8::Local<v8::PrimitiveArray> out = v8::PrimitiveArray::New(isolate, in->Length());
            for (uint32_t i = 0; i < in->Length(); ++i)
            {
                v8::Local<v8::Value> value = in->Get(context, i).ToLocalChecked();
                if (value->IsBoolean() || value->IsNumber() || value->IsString() || value->IsBigInt())
                {
                    out->Set(isolate, i, value.As<v8::Primitive>());
                }
                else
                {
                    v8pp::throw_type_error(isolate,
                                           "Invalid arguments, host defined options must be an primitive array");
                    return;
                }
            }

            hostDefinedOptions = out;
        }

        v8::Local<v8::Array> out = v8::Array::New(isolate, 2);

        v8::ScriptOrigin origin(specifier, 0, 0, false, -1, {}, false, false, false, hostDefinedOptions);

        v8::Local<v8::Value> null = v8::Null(isolate);
        v8::Local<v8::Script> script;
        if (!v8::Script::Compile(context, source, &origin).ToLocal(&script))
        {
            AXASSERT(tryCatch.HasCaught(), "op_eval_context - failed to catch compile script error");

            v8::Local<v8::Value> exception = tryCatch.Exception();

            EvalContextError e = {
                exception,
                is_instance_of_error(isolate, exception),
                true,
            };

            out->Set(context, 0, null).Check();
            out->Set(context, 1, e.to_v8(isolate)).Check();
            args.GetReturnValue().Set(out);
            return;
        }

        v8::Local<v8::Value> result;
        if (script->Run(context).ToLocal(&result))
        {
            out->Set(context, 0, result).Check();
            out->Set(context, 1, null).Check();
            args.GetReturnValue().Set(out);
            return;
        }
        else
        {
            AXASSERT(tryCatch.HasCaught(), "op_eval_context - failed to catch run script error");

            v8::Local<v8::Value> exception = tryCatch.Exception();

            EvalContextError e = {
                exception,
                is_instance_of_error(isolate, exception),
                false,
            };

            out->Set(context, 0, null).Check();
            out->Set(context, 1, e.to_v8(isolate)).Check();
            args.GetReturnValue().Set(out);
            return;
        }
    });
    mod.function("op_dispatch_exception", [](v8::Isolate* isolate, v8::Local<v8::Value> exception, bool isPromise) {
        (void)isPromise;

        v8::HandleScope scope(isolate);

        auto msg = v8::Exception::CreateMessage(isolate, exception);
        ax::JSEngine::reportException(isolate, msg, exception);
    });
    mod.function("op_encode", [](const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::Isolate* isolate = args.GetIsolate();
        v8::HandleScope scope(isolate);

        if (args.Length() < 1 || !args[0]->IsString())
        {
            v8pp::throw_type_error(isolate, "Invalid arguments");
            return;
        }

        v8::Local<v8::String> str = args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked();
        const auto len            = str->Utf8LengthV2(isolate);

        char* data = new char[len];
        str->WriteUtf8V2(isolate, data, len);

        auto backing_store = v8::ArrayBuffer::NewBackingStore(
            data, len, [](void* data, size_t length, void* deleter_data) { delete[] (reinterpret_cast<char*>(data)); },
            nullptr);

        v8::Local<v8::ArrayBuffer> array_buffer = v8::ArrayBuffer::New(isolate, std::move(backing_store));
        args.GetReturnValue().Set(array_buffer);
    });
    mod.function("op_decode", [](const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::Isolate* isolate = args.GetIsolate();
        v8::HandleScope scope(isolate);

        if (args.Length() < 1 || !args[0]->IsTypedArray())
        {
            v8pp::throw_type_error(isolate, "Invalid arguments");
            return;
        }

        v8::Local<v8::Uint8Array> v8Buffer = v8::Local<v8::Uint8Array>::Cast(args[0]);

        const char* buffer = static_cast<const char*>(v8Buffer->Buffer()->Data()) + v8Buffer->ByteOffset();
        size_t length      = v8Buffer->ByteLength();

        // Strip BOM
        if (length >= 3 && buffer[0] == char(0xEF) && buffer[1] == char(0xBB) && buffer[2] == char(0xBF))
        {
            buffer = buffer + 3;
            length -= 3;
        }

        v8::Local<v8::String> str;
        if (v8::String::NewFromUtf8(isolate, buffer, v8::NewStringType::kNormal, length).ToLocal(&str))
        {
            args.GetReturnValue().Set(str);
        }
        else
        {
            v8pp::throw_range_error(isolate, "string too long");
        }
    });
    mod.function("op_encode_binary_string", [](const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::Isolate* isolate = args.GetIsolate();
        v8::HandleScope scope(isolate);

        if (args.Length() < 1 || !args[0]->IsTypedArray())
        {
            v8pp::throw_type_error(isolate, "Invalid arguments");
            return;
        }

        v8::Local<v8::Uint8Array> v8Buffer = v8::Local<v8::Uint8Array>::Cast(args[0]);

        const uint8_t* buffer = static_cast<const uint8_t*>(v8Buffer->Buffer()->Data()) + v8Buffer->ByteOffset();
        size_t length         = v8Buffer->ByteLength();

        v8::Local<v8::String> str;
        if (v8::String::NewFromOneByte(isolate, buffer, v8::NewStringType::kNormal, length).ToLocal(&str))
        {
            args.GetReturnValue().Set(str);
        }
        else
        {
            v8pp::throw_range_error(isolate, "string too long");
        }
    });
    mod.function("op_serialize", op_serialize);
    mod.function("op_deserialize", op_deserialize);
}

class SerdeDelegate : public v8::ValueSerializer::Delegate, public v8::ValueDeserializer::Delegate
{
public:
    SerdeDelegate(v8::Isolate* isolate, v8::Local<v8::Function> errorCallback)
        : _isolate(isolate), _errorCallback(errorCallback)
    {}

    void ThrowDataCloneError(v8::Local<v8::String> message) override
    {
        v8::HandleScope scope(_isolate);
        if (!_errorCallback.IsEmpty())
        {
            v8::TryCatch tryCatch(_isolate);
            v8::Local<v8::Value> args[] = {message};
            (void)_errorCallback->Call(_isolate->GetCurrentContext(), v8::Undefined(_isolate), 1, args);
            if (tryCatch.HasCaught() || tryCatch.HasTerminated())
            {
                tryCatch.ReThrow();
                return;
            }
        }

        v8::Local<v8::Value> exception = v8::Exception::TypeError(message);
        _isolate->ThrowException(exception);
    }

private:
    v8::Isolate* _isolate;
    v8::Local<v8::Function> _errorCallback;
};

static v8::Local<v8::Value> op_serialize(v8::Isolate* isolate,
                                         v8::Local<v8::Value> value,
                                         v8::Local<v8::Value> hostObjects,
                                         v8::Local<v8::Value> transferredArrayBuffers,
                                         bool forStorage,
                                         v8::Local<v8::Value> errorCallback)
{
    if (!errorCallback->IsNullOrUndefined() && !errorCallback->IsFunction())
    {
        return v8pp::throw_type_error(isolate, "Error callback must be a function");
    }

    if (!hostObjects->IsNullOrUndefined() && !hostObjects->IsArray())
    {
        return v8pp::throw_type_error(isolate, "Host objects must be an array");
    }

    if (!transferredArrayBuffers->IsNullOrUndefined() && !transferredArrayBuffers->IsArray())
    {
        return v8pp::throw_type_error(isolate, "Transferred array buffers must be an array");
    }

    SerdeDelegate* delegate =
        new SerdeDelegate(isolate, errorCallback->IsNullOrUndefined() ? v8::Local<v8::Function>()
                                                                      : v8::Local<v8::Function>::Cast(errorCallback));
    v8::ValueSerializer serializer(isolate, delegate);
    serializer.WriteHeader();

    v8::TryCatch tryCatch(isolate);
    auto ret = serializer.WriteValue(isolate->GetCurrentContext(), value);
    if (tryCatch.HasCaught() || tryCatch.HasTerminated())
    {
        tryCatch.ReThrow();
        return {};
    }
    else if (ret.FromMaybe(false))
    {
        auto [data, size] = serializer.Release();
        auto backingStore =
            v8::ArrayBuffer::NewBackingStore(data, size, [](void* data, size_t length, void* deleter_data) {
            delete[] (reinterpret_cast<uint8_t*>(data));
        }, nullptr);
        v8::Local<v8::ArrayBuffer> arrayBuffer = v8::ArrayBuffer::New(isolate, std::move(backingStore));
        v8::Local<v8::Uint8Array> uint8Array   = v8::Uint8Array::New(arrayBuffer, 0, size);
        return uint8Array;
    }
    else
    {
        return v8pp::throw_type_error(isolate, "Failed to serialize value");
    }
}

static v8::Local<v8::Value> op_deserialize(v8::Isolate* isolate,
                                           v8::Local<v8::Value> buffer,
                                           v8::Local<v8::Value> hostObjects,
                                           v8::Local<v8::Value> transferredArrayBuffers,
                                           bool forStorage)
{
    if (!hostObjects->IsNullOrUndefined() && !hostObjects->IsArray())
    {
        return v8pp::throw_type_error(isolate, "Host objects must be an array");
    }

    if (!transferredArrayBuffers->IsNullOrUndefined() && !transferredArrayBuffers->IsArray())
    {
        return v8pp::throw_type_error(isolate, "Transferred array buffers must be an array");
    }

    if (!buffer->IsArrayBuffer() || !buffer->IsArrayBufferView())
    {
        return v8pp::throw_type_error(isolate, "Buffer must be an array buffer or array buffer view");
    }

    uint8_t* data = nullptr;
    size_t size   = 0;
    if (buffer->IsArrayBuffer())
    {
        v8::Local<v8::ArrayBuffer> arrayBuffer = v8::Local<v8::ArrayBuffer>::Cast(buffer);
        data                                   = static_cast<uint8_t*>(arrayBuffer->Data());
        size                                   = arrayBuffer->ByteLength();
    }
    else
    {
        v8::Local<v8::ArrayBufferView> arrayBufferView = v8::Local<v8::ArrayBufferView>::Cast(buffer);
        data = static_cast<uint8_t*>(arrayBufferView->Buffer()->Data()) + arrayBufferView->ByteOffset();
        size = arrayBufferView->ByteLength();
    }

    if (data == nullptr || size == 0)
    {
        return v8pp::throw_type_error(isolate, "Buffer is empty");
    }

    SerdeDelegate* delegate = new SerdeDelegate(isolate, {});
    v8::ValueDeserializer deserializer(isolate, data, size, delegate);

    auto parsedHeader = deserializer.ReadHeader(isolate->GetCurrentContext());
    if (!parsedHeader.FromMaybe(false))
    {
        return v8pp::throw_range_error(isolate, "Could not deserialize value");
    }

    auto result = deserializer.ReadValue(isolate->GetCurrentContext());
    if (result.IsEmpty())
    {
        return v8pp::throw_range_error(isolate, "Could not deserialize value");
    }

    return result.ToLocalChecked();
}
