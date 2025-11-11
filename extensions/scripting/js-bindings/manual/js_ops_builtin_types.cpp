#include "js-bindings/manual/js_bootstrap_bindings.h"

void js_bind_ops_builtin_types(v8pp::module& mod)
{
    fast_call(mod, "op_is_any_array_buffer",
              +[](v8::Local<v8::Value> v) { return v->IsArrayBuffer() || v->IsSharedArrayBuffer(); });
    // op_is_arguments_object,
    fast_call(mod, "op_is_arguments_object", +[](v8::Local<v8::Value> v) { return v->IsArgumentsObject(); });
    fast_call(mod, "op_is_array_buffer", +[](v8::Local<v8::Value> v) { return v->IsArrayBuffer(); });
    fast_call(mod, "op_is_array_buffer_view", +[](v8::Local<v8::Value> v) { return v->IsArrayBufferView(); });
    fast_call(mod, "op_is_async_function", +[](v8::Local<v8::Value> v) { return v->IsAsyncFunction(); });
    fast_call(mod, "op_is_big_int_object", +[](v8::Local<v8::Value> v) { return v->IsBigIntObject(); });
    fast_call(mod, "op_is_boolean_object", +[](v8::Local<v8::Value> v) { return v->IsBooleanObject(); });
    fast_call(mod, "op_is_boxed_primitive", +[](v8::Local<v8::Value> v) {
        return v->IsBooleanObject() || v->IsStringObject() || v->IsNumberObject() || v->IsSymbolObject() ||
               v->IsBigIntObject();
    });
    fast_call(mod, "op_is_data_view", +[](v8::Local<v8::Value> v) { return v->IsDataView(); });
    fast_call(mod, "op_is_date", +[](v8::Local<v8::Value> v) { return v->IsDate(); });
    fast_call(mod, "op_is_generator_function", +[](v8::Local<v8::Value> v) { return v->IsGeneratorFunction(); });
    fast_call(mod, "op_is_generator_object", +[](v8::Local<v8::Value> v) { return v->IsGeneratorObject(); });
    fast_call(mod, "op_is_map", +[](v8::Local<v8::Value> v) { return v->IsMap(); });
    fast_call(mod, "op_is_map_iterator", +[](v8::Local<v8::Value> v) { return v->IsMapIterator(); });
    fast_call(mod, "op_is_module_namespace_object",
              +[](v8::Local<v8::Value> v) { return v->IsModuleNamespaceObject(); });
    fast_call(mod, "op_is_native_error", +[](v8::Local<v8::Value> v) { return v->IsNativeError(); });
    fast_call(mod, "op_is_number_object", +[](v8::Local<v8::Value> v) { return v->IsNumberObject(); });
    fast_call(mod, "op_is_promise", +[](v8::Local<v8::Value> v) { return v->IsPromise(); });
    fast_call(mod, "op_is_proxy", +[](v8::Local<v8::Value> v) { return v->IsProxy(); });
    fast_call(mod, "op_is_reg_exp", +[](v8::Local<v8::Value> v) { return v->IsRegExp(); });
    fast_call(mod, "op_is_set", +[](v8::Local<v8::Value> v) { return v->IsSet(); });
    fast_call(mod, "op_is_set_iterator", +[](v8::Local<v8::Value> v) { return v->IsSetIterator(); });
    fast_call(mod, "op_is_shared_array_buffer", +[](v8::Local<v8::Value> v) { return v->IsSharedArrayBuffer(); });
    fast_call(mod, "op_is_string_object", +[](v8::Local<v8::Value> v) { return v->IsStringObject(); });
    fast_call(mod, "op_is_symbol_object", +[](v8::Local<v8::Value> v) { return v->IsSymbolObject(); });
    fast_call(mod, "op_is_typed_array", +[](v8::Local<v8::Value> v) { return v->IsTypedArray(); });
    fast_call(mod, "op_is_weak_map", +[](v8::Local<v8::Value> v) { return v->IsWeakMap(); });
    fast_call(mod, "op_is_weak_set", +[](v8::Local<v8::Value> v) { return v->IsWeakSet(); });
}
