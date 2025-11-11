#pragma once

#include <string_view>
#include <v8.h>

#include "axmol/base/Object.h"
#include "axmol/base/RefPtr.h"
#include "js-bindings/manual/js_isolate_properties.h"

namespace ax
{

class JSCallbackObject : public ax::Object
{
public:
    static ax::RefPtr<JSCallbackObject> get_or_create(v8::Isolate* isolate, v8::Local<v8::Function> func);
    ~JSCallbackObject() override;

    JSCallbackObject(const JSCallbackObject&)            = delete;
    JSCallbackObject& operator=(const JSCallbackObject&) = delete;
    JSCallbackObject(JSCallbackObject&&)            = delete;
    JSCallbackObject& operator=(JSCallbackObject&&) = delete;

    v8::Isolate* isolate() const { return _isolate; }

    v8::MaybeLocal<v8::Value> call_v8(int argc, v8::Local<v8::Value> argv[]);
private:
    JSCallbackObject(v8::Isolate* isolate, v8::Global<v8::Function> func);

    v8::Isolate* _isolate;
    v8::Global<v8::Function> _callback;
};

class IsolateData
{
public:
    IsolateData(v8::Isolate*);
    ~IsolateData();

    IsolateData(const IsolateData&)            = delete;
    IsolateData& operator=(const IsolateData&) = delete;
    IsolateData(IsolateData&&)                 = delete;
    IsolateData& operator=(IsolateData&&)      = delete;

    std::unordered_map<int, std::unordered_set<JSCallbackObject*>>& callbackMap() { return _callbackMap; }

#define VY(PropertyName, StringValue) V(v8::Symbol, PropertyName)
#define VS(PropertyName, StringValue) V(v8::String, PropertyName)
#define V(TypeName, PropertyName) \
    inline v8::Local<TypeName> PropertyName() const { return _##PropertyName.Get(_isolate); }
    PER_ISOLATE_SYMBOL_PROPERTIES(VY)
    PER_ISOLATE_STRING_PROPERTIES(VS)
#undef V
#undef VS
#undef VY

#define V(PrototypeName) \
    inline v8::Local<v8::Object> proto_##PrototypeName() const { return _proto_##PrototypeName.Get(_isolate); }
    PER_ISOLATE_CLASS_PROTOTYPE(V)
#undef V

    void registerConversionPrototype(std::string_view name, v8::Local<v8::Object> prototype);

private:
    void create_properties();

#define VY(PropertyName, StringValue) V(v8::Symbol, PropertyName)
#define VS(PropertyName, StringValue) V(v8::String, PropertyName)
#define V(TypeName, PropertyName)     v8::Eternal<TypeName> _##PropertyName;
    PER_ISOLATE_SYMBOL_PROPERTIES(VY)
    PER_ISOLATE_STRING_PROPERTIES(VS)
#undef V
#undef VS
#undef VY

#define V(PrototypeName) v8::Global<v8::Object> _proto_##PrototypeName;
    PER_ISOLATE_CLASS_PROTOTYPE(V)
#undef V

    std::unordered_map<int, std::unordered_set<JSCallbackObject*>> _callbackMap;
    v8::Isolate* _isolate;
};

} // namespace ax
