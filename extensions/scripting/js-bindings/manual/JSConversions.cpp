#include "js-bindings/manual/JSConversions.h"

#include "axmol/base/Director.h"
#include "axmol/base/Scheduler.h"
#include "axmol/base/Value.h"
#include "axmol/2d/Node.h"
#include "axmol/math/Color.h"
#include "manual/JSEngine.h"

#include "v8pp/class.hpp"
#include "v8pp/convert.hpp"
#include "v8pp/object.hpp"

ax::Value v8pp::convert<ax::Value>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    v8::HandleScope scope(isolate);
    auto context = isolate->GetCurrentContext();

    if (value.IsEmpty() || value->IsNullOrUndefined())
    {
        return ax::Value::Null;
    }

    if (value->IsBoolean())
    {
        return ax::Value(value->BooleanValue(isolate));
    }

    if (value->IsInt32())
    {
        return ax::Value(value->Int32Value(context).ToChecked());
    }

    if (value->IsUint32())
    {
        return ax::Value(value->Uint32Value(context).ToChecked());
    }

    if (value->IsBigInt())
    {
        return ax::Value(value->ToBigInt(context).ToLocalChecked()->Int64Value());
    }

    if (value->IsNumber())
    {
        return ax::Value(value->NumberValue(context).ToChecked());
    }

    if (value->IsString())
    {
        return ax::Value(v8pp::from_v8<std::string>(isolate, value));
    }

    if (value->IsArray())
    {
        return ax::Value(v8pp::from_v8<ax::ValueVector>(isolate, value));
    }

    if (value->IsObject())
    {
        return ax::Value(v8pp::from_v8<ax::ValueMap>(isolate, value));
    }

    throw v8pp::invalid_argument(isolate, value, "Value");
}

v8::Local<v8::Value> v8pp::convert<ax::Value>::to_v8(v8::Isolate* isolate, ax::Value const& value)
{
    v8::EscapableHandleScope scope(isolate);
    auto context = isolate->GetCurrentContext();

    switch (value.getType())
    {
    case ax::Value::Type::NONE:
        return scope.Escape(v8::Null(isolate));
    case ax::Value::Type::BOOLEAN:
        return scope.Escape(v8::Boolean::New(isolate, value.asBool()));
    case ax::Value::Type::INT_I32:
        return scope.Escape(v8::Int32::New(isolate, value.asInt()));
    case ax::Value::Type::INT_UI32:
        return scope.Escape(v8::Uint32::New(isolate, value.asUint()));
    case ax::Value::Type::INT_I64:
        return scope.Escape(v8::BigInt::New(isolate, value.asInt64()));
    case ax::Value::Type::INT_UI64:
        return scope.Escape(v8::BigInt::NewFromUnsigned(isolate, value.asUint64()));
    case ax::Value::Type::FLOAT:
        return scope.Escape(v8::Number::New(isolate, value.asFloat()));
    case ax::Value::Type::DOUBLE:
        return scope.Escape(v8::Number::New(isolate, value.asDouble()));
    case ax::Value::Type::STRING:
        return scope.Escape(v8pp::to_v8(isolate, value.asStringRef()));
    case ax::Value::Type::VECTOR:
    {
        const ax::ValueVector& vec = value.asValueVector();
        auto ret                   = v8::Array::New(isolate, vec.size());

        uint32_t i = 0;
        for (const ax::Value& ele : vec)
        {
            ret->Set(context, i++, v8pp::convert<ax::Value>::to_v8(isolate, ele)).Check();
        }

        return scope.Escape(ret);
    }
    case ax::Value::Type::MAP:
    {
        const ax::ValueMap& map = value.asValueMap();

        auto ret = v8::Object::New(isolate);
        for (const auto& [key, val] : map)
        {
            ret->Set(context, v8pp::convert<std::string>::to_v8(isolate, key),
                     v8pp::convert<ax::Value>::to_v8(isolate, val))
                .Check();
        }

        return scope.Escape(ret);
    }
    case ax::Value::Type::INT_KEY_MAP:
    {
        const ax::ValueMapIntKey& map = value.asIntKeyMap();

        auto ret = v8::Object::New(isolate);
        for (const auto& [key, val] : map)
        {
            auto v8Key = v8::Integer::New(isolate, key);
            ret->Set(context, v8Key, v8pp::convert<ax::Value>::to_v8(isolate, val)).Check();
        }

        return scope.Escape(ret);
    }
    default:
        AXASSERT(false, "UNREACHABLE");
        return scope.Escape(v8::Null(isolate));
    }
}

bool v8pp::convert<ax::Data>::is_valid(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    return value->IsArrayBuffer() || value->IsArrayBufferView();
}

ax::Data v8pp::convert<ax::Data>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    if (!is_valid(isolate, value))
    {
        throw v8pp::invalid_argument(isolate, value, "ax::Data");
    }

    v8::HandleScope scope(isolate);
    if (value->IsArrayBuffer())
    {
        auto arrayBuffer    = value.As<v8::ArrayBuffer>();
        const uint8_t* data = static_cast<const uint8_t*>(arrayBuffer->Data());

        ax::Data outData;
        size_t copiedSize = outData.copy(data, arrayBuffer->ByteLength());
        AXASSERT(copiedSize == arrayBuffer->ByteLength(), "ax::Data from_v8 copy failed");

        return outData;
    }

    auto arrayBufferView = value.As<v8::ArrayBufferView>();

    ax::Data outData;
    uint8_t* writePtr = outData.resize(arrayBufferView->ByteLength());
    size_t copiedSize = arrayBufferView->CopyContents(writePtr, outData.size());
    AXASSERT(copiedSize == arrayBufferView->ByteLength(), "ax::Data from_v8 copy failed");

    return outData;
}

static void axDataDeleter(void* data, size_t length, void*)
{
    free(data);
}

v8::Local<v8::Value> v8pp::convert<ax::Data>::to_v8(v8::Isolate* isolate, ax::Data const& value)
{
    v8::EscapableHandleScope scope(isolate);

    if (value.isNull())
    {
        return v8::Null(isolate);
    }

    ssize_t size  = 0;
    uint8_t* data = const_cast<ax::Data&>(value).takeBuffer(&size);
    if (size == 0 || data == nullptr)
    {
        return v8::Null(isolate);
    }

    auto backingStore                    = v8::ArrayBuffer::NewBackingStore(data, size, axDataDeleter, nullptr);
    auto arrayBuffer                     = v8::ArrayBuffer::New(isolate, std::move(backingStore));
    v8::Local<v8::Uint8Array> uint8Array = v8::Uint8Array::New(arrayBuffer, 0, size);
    return scope.Escape(uint8Array);
}

bool v8pp::convert<ax::Mat4>::is_valid(v8::Isolate*, v8::Local<v8::Value> value)
{
    return !value.IsEmpty() && value->IsArray();
}

ax::Mat4 v8pp::convert<ax::Mat4>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    if (!is_valid(isolate, value))
    {
        throw v8pp::invalid_argument(isolate, value, "ax::Mat4");
    }

    v8::HandleScope scope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Array> array     = value.As<v8::Array>();
    if (array->Length() != 16)
    {
        throw v8pp::invalid_argument(isolate, value, "ax::Mat4");
    }

    ax::Mat4 ret;
    for (uint32_t i = 0; i < 16; ++i)
    {
        ret.m[i] = v8pp::from_v8<float>(isolate, array->Get(context, i).ToLocalChecked());
    }

    return ret;
}

v8::Local<v8::Value> v8pp::convert<ax::Mat4>::to_v8(v8::Isolate* isolate, const ax::Mat4& value)
{
    v8::EscapableHandleScope scope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();

    v8::Local<v8::Array> ret = v8::Array::New(isolate, 16);
    for (uint32_t i = 0; i < 16; ++i)
    {
        ret->Set(context, i, v8pp::to_v8(isolate, value.m[i])).Check();
    }

    return ret;
}

#define FOREACH_IMPL(MACRO, ARG, ...)   MACRO(ARG) __VA_OPT__(FOREACH_IMPL_1(MACRO, __VA_ARGS__))
#define FOREACH_IMPL_1(MACRO, ARG, ...) MACRO(ARG) __VA_OPT__(FOREACH_IMPL_2(MACRO, __VA_ARGS__))
#define FOREACH_IMPL_2(MACRO, ARG, ...) MACRO(ARG) __VA_OPT__(FOREACH_IMPL_3(MACRO, __VA_ARGS__))
#define FOREACH_IMPL_3(MACRO, ARG, ...) MACRO(ARG) __VA_OPT__(FOREACH_IMPL_4(MACRO, __VA_ARGS__))
#define FOREACH_IMPL_4(MACRO, ARG, ...) MACRO(ARG) __VA_OPT__(FOREACH_IMPL_5(MACRO, __VA_ARGS__))
#define FOREACH_IMPL_5(MACRO, ARG, ...) MACRO(ARG) __VA_OPT__(FOREACH_IMPL_6(MACRO, __VA_ARGS__))
#define FOREACH_IMPL_6(MACRO, ARG, ...) MACRO(ARG) __VA_OPT__(FOREACH_IMPL_7(MACRO, __VA_ARGS__))
#define FOREACH_IMPL_7(MACRO, ARG, ...) MACRO(ARG) __VA_OPT__(FOREACH_IMPL_8(MACRO, __VA_ARGS__))
#define FOREACH_IMPL_8(MACRO, ARG, ...) MACRO(ARG)
#define FOREACH(MACRO, ...)             __VA_OPT__(FOREACH_IMPL(MACRO, __VA_ARGS__))

#define STRING_CONCAT_IMPL(a, b)        a##b
#define STRING_CONCAT(a, b)             STRING_CONCAT_IMPL(a, b)

#define JS_CONVERT_FIELD_DATA(field)    ok &= object_get(isolate, object, ext.STRING_CONCAT(field, _string)(), ret.field);
#define JS_CONVERT_FIELD_NAMES(field)   ext.STRING_CONCAT(field, _string)(),
#define JS_CONVERT_FIELD_VALUES(field)  v8pp::to_v8(isolate, value.field),

#define JS_CONVERT_FOR_DATA_STRUCT(Type, ...)                                                                  \
    bool v8pp::convert<Type>::is_valid(v8::Isolate*, v8::Local<v8::Value> value)                               \
    {                                                                                                          \
        return !value.IsEmpty() && value->IsObject();                                                          \
    }                                                                                                          \
                                                                                                               \
    Type v8pp::convert<Type>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> value)                        \
    {                                                                                                          \
        if (!is_valid(isolate, value))                                                                         \
        {                                                                                                      \
            throw v8pp::invalid_argument(isolate, value, #Type);                                               \
        }                                                                                                      \
                                                                                                               \
        v8::HandleScope scope(isolate);                                                                        \
        auto& ext   = ax::JSEngine::fromIsolate(isolate)->ext();                                               \
        auto object = value.As<v8::Object>();                                                                  \
        Type ret{};                                                                                            \
        bool ok = true;                                                                                        \
        FOREACH(JS_CONVERT_FIELD_DATA, __VA_ARGS__);                                                           \
        if (!ok)                                                                                               \
        {                                                                                                      \
            throw v8pp::invalid_argument(isolate, value, #Type);                                               \
        }                                                                                                      \
        return ret;                                                                                            \
    }                                                                                                          \
                                                                                                               \
    v8::Local<v8::Value> v8pp::convert<Type>::to_v8(v8::Isolate* isolate, Type const& value)                   \
    {                                                                                                          \
        v8::EscapableHandleScope scope(isolate);                                                               \
        auto& ext                     = ax::JSEngine::fromIsolate(isolate)->ext();                             \
        v8::Local<v8::Name> names[]   = {FOREACH(JS_CONVERT_FIELD_NAMES, __VA_ARGS__)};                        \
        v8::Local<v8::Value> values[] = {FOREACH(JS_CONVERT_FIELD_VALUES, __VA_ARGS__)};                       \
        auto ret = v8::Object::New(isolate, TO_V8_PROTOTYPE, names, values, sizeof(names) / sizeof(names[0])); \
        return scope.Escape(ret);                                                                              \
    }

#define JS_CONVERT_MAPPED_FIELD_DATA(ACCESSOR, NAME) \
    ok &= object_get(isolate, object, ext.STRING_CONCAT(NAME, _string)(), ret.ACCESSOR);

#define JS_CONVERT_MAPPED_FIELD_NAMES(ACCESSOR, NAME)  ext.STRING_CONCAT(NAME, _string)(),
#define JS_CONVERT_MAPPED_FIELD_VALUES(ACCESSOR, NAME) v8pp::to_v8(isolate, value.ACCESSOR),

#define JS_CONVERT_FOR_DATA_STRUCT_MAPPED_FIELD(Type, X_FIELD)                                                 \
    bool v8pp::convert<Type>::is_valid(v8::Isolate*, v8::Local<v8::Value> value)                               \
    {                                                                                                          \
        return !value.IsEmpty() && value->IsObject();                                                          \
    }                                                                                                          \
                                                                                                               \
    Type v8pp::convert<Type>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> value)                        \
    {                                                                                                          \
        if (!is_valid(isolate, value))                                                                         \
        {                                                                                                      \
            throw v8pp::invalid_argument(isolate, value, #Type);                                               \
        }                                                                                                      \
                                                                                                               \
        v8::HandleScope scope(isolate);                                                                        \
        auto& ext   = ax::JSEngine::fromIsolate(isolate)->ext();                                               \
        auto object = value.As<v8::Object>();                                                                  \
        Type ret{};                                                                                            \
        bool ok = true;                                                                                        \
        X_FIELD(JS_CONVERT_MAPPED_FIELD_DATA)                                                                  \
        if (!ok)                                                                                               \
        {                                                                                                      \
            throw v8pp::invalid_argument(isolate, value, #Type);                                               \
        }                                                                                                      \
        return ret;                                                                                            \
    }                                                                                                          \
                                                                                                               \
    v8::Local<v8::Value> v8pp::convert<Type>::to_v8(v8::Isolate* isolate, Type const& value)                   \
    {                                                                                                          \
        v8::EscapableHandleScope scope(isolate);                                                               \
        auto& ext                     = ax::JSEngine::fromIsolate(isolate)->ext();                             \
        v8::Local<v8::Name> names[]   = {X_FIELD(JS_CONVERT_MAPPED_FIELD_NAMES)};                              \
        v8::Local<v8::Value> values[] = {X_FIELD(JS_CONVERT_MAPPED_FIELD_VALUES)};                             \
        auto ret = v8::Object::New(isolate, TO_V8_PROTOTYPE, names, values, sizeof(names) / sizeof(names[0])); \
        return scope.Escape(ret);                                                                              \
    }

#define TO_V8_PROTOTYPE ext.proto_Vec2()
JS_CONVERT_FOR_DATA_STRUCT(ax::Vec2, x, y);
#undef TO_V8_PROTOTYPE

#define TO_V8_PROTOTYPE ext.proto_Vec3()
JS_CONVERT_FOR_DATA_STRUCT(ax::Vec3, x, y, z);
#undef TO_V8_PROTOTYPE

#define TO_V8_PROTOTYPE ext.proto_Vec4()
JS_CONVERT_FOR_DATA_STRUCT(ax::Vec4, x, y, z, w);
#undef TO_V8_PROTOTYPE

#define TO_V8_PROTOTYPE ext.proto_Rect()
#define RECT_FIELDS(X) \
    X(origin.x, x)     \
    X(origin.y, y)     \
    X(size.x, width)   \
    X(size.y, height)
JS_CONVERT_FOR_DATA_STRUCT_MAPPED_FIELD(ax::Rect, RECT_FIELDS);
#undef RECT_FIELDS
#undef TO_V8_PROTOTYPE

#define TO_V8_PROTOTYPE v8::Null(isolate)

#define PixelBufferDesc_Fields(X) \
    X(_data, data)         \
    X(_width, width)       \
    X(_height, height)
JS_CONVERT_FOR_DATA_STRUCT_MAPPED_FIELD(ax::rhi::PixelBufferDesc, PixelBufferDesc_Fields);
#undef PixelBufferDesc_Fields

JS_CONVERT_FOR_DATA_STRUCT(ax::rhi::RectI, x, y, width, height);
JS_CONVERT_FOR_DATA_STRUCT(ax::Color, r, g, b, a);
JS_CONVERT_FOR_DATA_STRUCT(ax::Color32, r, g, b, a);
JS_CONVERT_FOR_DATA_STRUCT(ax::AffineTransform, a, b, c, d, tx, ty);
JS_CONVERT_FOR_DATA_STRUCT(ax::ResourceData, type, file, plist);
JS_CONVERT_FOR_DATA_STRUCT(ax::BlendFunc, src, dst);
JS_CONVERT_FOR_DATA_STRUCT(ax::MeshVertexAttrib, type, vertexAttrib);
JS_CONVERT_FOR_DATA_STRUCT(ax::OffMeshLinkData, startPosition, endPosition);
JS_CONVERT_FOR_DATA_STRUCT(ax::PhysicsMaterial, density, restitution, friction);
JS_CONVERT_FOR_DATA_STRUCT(ax::Acceleration, x, y, z, timestamp);
JS_CONVERT_FOR_DATA_STRUCT(ax::HSV, h, s, v, a);
JS_CONVERT_FOR_DATA_STRUCT(ax::EmissionShape,
                           type,
                           x,
                           y,
                           innerWidth,
                           innerHeight,
                           outerWidth,
                           outerHeight,
                           innerRadius,
                           outerRadius,
                           coneOffset,
                           coneAngle,
                           edgeBias,
                           fourccId);
JS_CONVERT_FOR_DATA_STRUCT(ax::IMEKeyboardNotificationInfo, begin, end, duration);
JS_CONVERT_FOR_DATA_STRUCT(ax::extension::ManifestAsset, md5, path, compressed, size, downloadState);
JS_CONVERT_FOR_DATA_STRUCT(cocostudio::timeline::AnimationInfo, name, startIndex, endIndex);
JS_CONVERT_FOR_DATA_STRUCT(fairygui::Margin, left, top, right, bottom);
