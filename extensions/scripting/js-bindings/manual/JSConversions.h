#pragma once

#include "JSEngine.h"

#include <type_traits>
#include <functional>
#include <v8-value.h>

#include "v8pp/convert.hpp"
#include "v8pp/class.hpp"
#include "v8pp/module.hpp"

#include "axmol/2d/Label.h"
#include "axmol/3d/Bundle3DData.h"
#include "axmol/base/Data.h"
#include "axmol/base/RefPtr.h"
#include "axmol/base/IMEDelegate.h"
#include "axmol/base/Types.h"
#include "axmol/base/Value.h"
#include "axmol/base/Vector.h"
#include "axmol/math/Rect.h"
#include "axmol/math/Vec2.h"
#include "axmol/math/Vec3.h"
#include "axmol/math/Vec4.h"
#include "axmol/rhi/RHITypes.h"
#include "axmol/platform/RenderView.h"
#include "axmol/navmesh/NavMeshAgent.h"
#include "axmol/ui/GUIDefine.h"
#include "axmol/ui/UIWidget.h"

#include "cocostudio/ActionTimeline/ActionTimeline.h"
#include "fairygui/Margin.h"
#include "extensions/assets-manager/src/assets-manager/Manifest.h"

#include <tsl/robin_map.h>

template <typename T>
inline bool object_get(v8::Isolate* isolate, v8::Local<v8::Object> obj, v8::Local<v8::Name> propName, T& value)
{
    v8::Local<v8::Value> val;
    if (!obj->Get(isolate->GetCurrentContext(), propName).ToLocal(&val) || val->IsUndefined())
    {
        return false;
    }

    value = v8pp::from_v8<T>(isolate, val);
    return true;
}

template <>
struct v8pp::convert<ax::Value>
{
    using from_type = ax::Value;
    using to_type   = v8::Local<v8::Value>;

    static bool is_valid(v8::Isolate*, v8::Local<v8::Value>)
    {
        // All js value is a valid ax::Value
        return true;
    }

    static from_type from_v8(v8::Isolate* isolate, v8::Local<v8::Value> value);

    static to_type to_v8(v8::Isolate* isolate, ax::Value const& value);
};

template <>
struct v8pp::is_wrapped_class<ax::Value> : std::false_type
{};

template <typename T>
struct v8pp::convert<ax::Vector<T>>
{
    using from_type = ax::Vector<T>;
    using to_type   = v8::Local<v8::Array>;
    using item_type = T;

    static bool is_valid(v8::Isolate* isolate, v8::Local<v8::Value> value)
    {
        return !value.IsEmpty() && value->IsArray();
    }

    static from_type from_v8(v8::Isolate* isolate, v8::Local<v8::Value> value)
    {
        if (!is_valid(isolate, value))
        {
            throw invalid_argument(isolate, value, "Array");
        }

        v8::HandleScope scope(isolate);
        v8::Local<v8::Context> context = isolate->GetCurrentContext();
        v8::Local<v8::Array> array     = value.As<v8::Array>();

        ax::Vector<T> result{};
        result.reserve(array->Length());

        for (uint32_t i = 0, count = array->Length(); i < count; ++i)
        {
            v8::Local<v8::Value> v8Item = array->Get(context, i).ToLocalChecked();
            T item                      = v8pp::convert<item_type>::from_v8(isolate, v8Item);
            // if constexpr (std::is_pointer_v<T>)
            // {
            //     if (item == nullptr)
            //         continue;
            // }

            result.pushBack(std::move(item));
        }

        return result;
    }

    static to_type to_v8(v8::Isolate* isolate, ax::Vector<T> const& value)
    {
        constexpr int max_size = std::numeric_limits<int>::max();
        if (value.size() > max_size)
        {
            throw std::runtime_error("Invalid array length: actual " + std::to_string(value.size()) +
                                     " exceeds maximal " + std::to_string(max_size));
        }

        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::Context> context = isolate->GetCurrentContext();

        v8::Local<v8::Array> result = v8::Array::New(isolate, static_cast<int>(value.size()));

        uint32_t i = 0;
        for (item_type const& item : value)
        {
            result->Set(context, i++, v8pp::convert<item_type>::to_v8(isolate, item)).FromJust();
        }

        return scope.Escape(result);
    }
};

template <typename T>
struct v8pp::is_wrapped_class<ax::Vector<T>> : std::false_type
{};

template <typename K, typename V, typename Hash, typename Equal>
struct v8pp::convert<ax::Map<K, V, Hash, Equal>>
{
    using from_type = ax::Map<K, V, Hash, Equal>;
    using to_type   = v8::Local<v8::Object>;

    using Key   = K;
    using Value = V;

    static bool is_valid(v8::Isolate*, v8::Local<v8::Value> value)
    {
        return !value.IsEmpty() && value->IsObject() && !value->IsArray();
    }

    static from_type from_v8(v8::Isolate* isolate, v8::Local<v8::Value> value)
    {
        if (!is_valid(isolate, value))
        {
            throw invalid_argument(isolate, value, "Object");
        }

        v8::HandleScope scope(isolate);
        v8::Local<v8::Context> context  = isolate->GetCurrentContext();
        v8::Local<v8::Object> object    = value.As<v8::Object>();
        v8::Local<v8::Array> prop_names = object->GetPropertyNames(context).ToLocalChecked();

        from_type result{};
        for (uint32_t i = 0, count = prop_names->Length(); i < count; ++i)
        {
            v8::Local<v8::Value> key = prop_names->Get(context, i).ToLocalChecked();
            v8::Local<v8::Value> val = object->Get(context, key).ToLocalChecked();
            result.emplace(convert<Key>::from_v8(isolate, key), convert<Value>::from_v8(isolate, val));
        }
        return result;
    }

    static to_type to_v8(v8::Isolate* isolate, from_type const& value)
    {
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::Context> context = isolate->GetCurrentContext();
        v8::Local<v8::Object> result   = v8::Object::New(isolate);
        for (auto const& item : value)
        {
            result->Set(context, convert<Key>::to_v8(isolate, item.first), convert<Value>::to_v8(isolate, item.second))
                .FromJust();
        }

        return scope.Escape(result);
    }
};

template <typename K, typename V, typename Hash, typename Equal>
struct v8pp::is_wrapped_class<ax::Map<K, V, Hash, Equal>> : std::false_type
{};

template <>
struct v8pp::convert<void*>
{
    using from_type = void*;
    using to_type   = v8::Local<v8::Value>;

    static bool is_valid(v8::Isolate*, v8::Local<v8::Value>) { return false; }

    static from_type from_v8(v8::Isolate* isolate, v8::Local<v8::Value> value)
    {
        throw v8pp::invalid_argument(isolate, value, "convert to this type is not supported");
    }

    static to_type to_v8(v8::Isolate* isolate, void* const&) { return v8::Null(isolate); }
};

template <>
struct v8pp::is_wrapped_class<void*> : std::false_type
{};

template <>
struct v8pp::convert<const void*> : v8pp::convert<void*>
{};

template <>
struct v8pp::is_wrapped_class<const void*> : std::false_type
{};

template <>
struct v8pp::convert<float*>
{
    using from_type = float*;
    using to_type   = v8::Local<v8::Value>;

    static bool is_valid(v8::Isolate*, v8::Local<v8::Value>) { return false; }

    static from_type from_v8(v8::Isolate* isolate, v8::Local<v8::Value> value)
    {
        throw v8pp::invalid_argument(isolate, value, "convert to this type is not supported");
    }

    static to_type to_v8(v8::Isolate* isolate, from_type const&) { return v8::Null(isolate); }
};

template <>
struct v8pp::is_wrapped_class<float*> : std::false_type
{};

#define JS_CONVERT_FWD_DECLARE_DATA_STRUCT(Type)                                    \
    template <>                                                                     \
    struct v8pp::convert<Type>                                                      \
    {                                                                               \
        using from_type = Type;                                                     \
        using to_type   = v8::Local<v8::Value>;                                     \
                                                                                    \
        static bool is_valid(v8::Isolate*, v8::Local<v8::Value> value);             \
        static from_type from_v8(v8::Isolate* isolate, v8::Local<v8::Value> value); \
        static to_type to_v8(v8::Isolate* isolate, from_type const& value);         \
    };                                                                              \
    template <>                                                                     \
    struct v8pp::is_wrapped_class<Type> : std::false_type                           \
    {};

JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::Vec2);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::Vec3);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::Vec4);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::Rect);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::rhi::RectI);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::Mat4);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::AffineTransform);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::Color);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::Color32);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::Data);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::ResourceData);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::BlendFunc);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::MeshVertexAttrib);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::OffMeshLinkData);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::PhysicsMaterial);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::Acceleration);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::HSV);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::EmissionShape);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::IMEKeyboardNotificationInfo);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::rhi::PixelBufferDesc);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(ax::extension::ManifestAsset);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(cocostudio::timeline::AnimationInfo);
JS_CONVERT_FWD_DECLARE_DATA_STRUCT(fairygui::Margin);

#undef JS_CONVERT_FWD_DECLARE_DATA_STRUCT

template <typename Ret, typename... Args>
class JSCallback
{
public:
    JSCallback(v8::Isolate* isolate, v8::Local<v8::Function> func)
        : _impl(ax::JSCallbackObject::get_or_create(isolate, func))
    {
        AXASSERT(_impl != nullptr, "Failed to create JSCallback");
    }

    Ret operator()(Args... args) const
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        if (isolate != _impl->isolate())
        {
            if constexpr (std::is_same_v<Ret, void>)
                return;
            else
                return {};
        }

        v8::HandleScope scope(isolate);

        const int argCount = sizeof...(Args);
        // +1 to allocate array for arg_count == 0
        v8::Local<v8::Value> v8Args[argCount + 1] = {v8pp::to_v8(isolate, std::forward<Args>(args))...};

        v8::Local<v8::Value> result;
        if (_impl->call_v8(argCount, v8Args).ToLocal(&result))
        {
            if constexpr (std::is_same_v<Ret, void>)
                return;
            else
                return v8pp::from_v8<Ret>(isolate, result);
        }

        if constexpr (std::is_same_v<Ret, void>)
            return;
        else
            return {};
    }

private:
    ax::RefPtr<ax::JSCallbackObject> _impl;
};

template <typename Ret, typename... Args>
struct v8pp::convert<std::function<Ret(Args...)>>
{
    using from_type = std::function<Ret(Args...)>;
    using to_type   = v8::Local<v8::Value>;

    static bool is_valid(v8::Isolate*, v8::Local<v8::Value> value)
    {
        return !value.IsEmpty() && (value->IsNullOrUndefined() || value->IsFunction());
    }

    static from_type from_v8(v8::Isolate* isolate, v8::Local<v8::Value> value)
    {
        if (!is_valid(isolate, value))
        {
            throw v8pp::invalid_argument(isolate, value, "Function");
        }

        if (value->IsNullOrUndefined())
        {
            return nullptr;
        }

        return JSCallback<Ret, Args...>(isolate, value.As<v8::Function>());
    }

    static to_type to_v8(v8::Isolate* isolate, from_type const& value)
    {
        throw std::runtime_error("cannot convert std::function to js value");
    }
};
