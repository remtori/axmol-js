#pragma once

#include <algorithm>
#include <memory>
#include <optional>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "v8pp/config.hpp"
#include "v8pp/function.hpp"
#include "v8pp/property.hpp"
#include "v8pp/ptr_traits.hpp"
#include "v8pp/class_detail.hpp"

#if V8_MAJOR_VERSION > 13 || (V8_MAJOR_VERSION == 13 && V8_MINOR_VERSION >= 3)
#    include <v8-external-memory-accounter.h>
#endif

namespace v8pp::detail
{

struct class_info
{
    type_info const type;

    class_info(type_info const& type);

    virtual ~class_info() = default;  // make virtual to delete derived object_registry

    std::string class_name() const;
};

class object_registry final : public class_info
{
public:
    using pointer_type       = void*;
    using const_pointer_type = const void*;
    using object_id          = void*;

    using ctor_function =
        std::function<std::pair<pointer_type, size_t>(v8::FunctionCallbackInfo<v8::Value> const& args)>;
    using dtor_function = std::function<void(v8::Isolate*, pointer_type const&)>;
    using cast_function = pointer_type (*)(pointer_type const&);

    object_registry(v8::Isolate* isolate, type_info const& type, dtor_function&& dtor);

    object_registry(object_registry const&) = delete;
    object_registry(object_registry&&)      = default;

    object_registry& operator=(object_registry const&) = delete;
    object_registry& operator=(object_registry&&)      = delete;

    ~object_registry();

    v8::Isolate* isolate() { return isolate_; }

    v8::Local<v8::FunctionTemplate> js_function_template() { return to_local(isolate_, js_func_); }

    void set_auto_wrap_objects(bool auto_wrap) { auto_wrap_objects_ = auto_wrap; }
    bool auto_wrap_objects() const { return auto_wrap_objects_; }

    void set_only_reference_objects(bool only_ref) { only_reference_objects_ = only_ref; }
    bool only_reference_objects() const { return only_reference_objects_; }

    void set_ctor(ctor_function&& ctor);

    void set_base(object_registry& info, cast_function cast);
    bool cast(pointer_type& ptr, type_info const& actual_type) const;

    void remove_object(object_id const& obj);
    void remove_objects();

    pointer_type find_object(object_id id, type_info const& actual_type) const;
    v8::Local<v8::Object> find_v8_object(pointer_type const& ptr) const;

    v8::Local<v8::Object> wrap_object(pointer_type const& object, size_t size);
    v8::Local<v8::Object> wrap_object(v8::FunctionCallbackInfo<v8::Value> const& args);
    pointer_type unwrap_object(v8::Local<v8::Value> value);

private:
    struct wrapped_object
    {
        v8::Global<v8::Object> pobj;
        size_t size;  // 0 for referenced objects
    };

    void reset_object(pointer_type const& object, wrapped_object& wrapped);

    struct base_class_info
    {
        object_registry& info;
        cast_function cast;

        base_class_info(object_registry& info, cast_function cast) : info(info), cast(cast) {}
    };

    std::optional<base_class_info> base_;
    std::vector<object_registry*> derivatives_;
    std::unordered_map<pointer_type, wrapped_object> objects_;

    v8::Isolate* isolate_;
    v8::Global<v8::FunctionTemplate> js_func_;

#if V8_MAJOR_VERSION > 13 || (V8_MAJOR_VERSION == 13 && V8_MINOR_VERSION >= 3)
    v8::ExternalMemoryAccounter external_memory_accounter_;

    void increase_allocated_memory(size_t size) { external_memory_accounter_.Increase(isolate_, size); }

    void decrease_allocated_memory(size_t size) { external_memory_accounter_.Decrease(isolate_, size); }
#else
    void increase_allocated_memory(size_t size)
    {
        isolate_->AdjustAmountOfExternalAllocatedMemory(static_cast<int64_t>(size));
    }
    void decrease_allocated_memory(size_t size)
    {
        isolate_->AdjustAmountOfExternalAllocatedMemory(-static_cast<int64_t>(size));
    }
#endif

    ctor_function ctor_;
    dtor_function dtor_;
    bool auto_wrap_objects_;
    bool only_reference_objects_;
};

class classes
{
public:
    static object_registry& add(v8::Isolate* isolate,
                                type_info const& type,
                                typename object_registry::dtor_function&& dtor);

    static void remove(v8::Isolate* isolate, type_info const& type);

    static object_registry& find(v8::Isolate* isolate, type_info const& base_type, type_info const& actual_type);
    static object_registry& find(v8::Isolate* isolate, type_info const& type);

    static void remove_all(v8::Isolate* isolate);

private:
    using classes_info = std::vector<std::unique_ptr<class_info>>;
    classes_info classes_;

    classes_info::iterator find(type_info const& type);

    enum class operation
    {
        get,
        add,
        remove
    };
    static classes* instance(operation op, v8::Isolate* isolate);
};

}  // namespace v8pp::detail

namespace v8pp
{

/// Interface to access C++ classes bound to V8
template <typename T, typename Traits = object_ptr_traits>
class class_
{
    static_assert(is_wrapped_class<T>::value, "T must be a user-defined class");

    using object_registry = detail::object_registry;
    object_registry& class_info_;

    using object_id          = typename object_registry::object_id;
    using pointer_type       = typename object_registry::pointer_type;
    using const_pointer_type = typename object_registry::const_pointer_type;

public:
    using object_pointer_type       = typename Traits::template object_pointer_type<T>;
    using object_const_pointer_type = typename Traits::template object_const_pointer_type<T>;

    using ctor_function = std::function<object_pointer_type(v8::FunctionCallbackInfo<v8::Value> const& args)>;
    using dtor_function = std::function<void(v8::Isolate* isolate, object_pointer_type const& obj)>;

private:
    template <typename... Args>
    static object_pointer_type object_create(Args&&... args)
    {
        return Traits::template create<T>(std::forward<Args>(args)...);
    }

    template <typename... Args>
    struct object_create_from_v8
    {
        static object_pointer_type call(v8::FunctionCallbackInfo<v8::Value> const& args)
        {
            return detail::call_from_v8<Traits>(Traits::template create<T, Args...>, args);
        }
    };

    static void object_destroy(v8::Isolate*, pointer_type const& ptr)
    {
        Traits::destroy(Traits::template static_pointer_cast<T>(ptr));
    }

    explicit class_(v8::Isolate* isolate, detail::type_info const& existing)
        : class_info_(detail::classes::find(isolate, existing))
    {}

public:
    explicit class_(v8::Isolate* isolate, dtor_function destroy = &object_destroy)
        : class_info_(
              detail::classes::add(isolate,
                                   detail::type_id<T>(),
                                   [destroy = std::move(destroy)](v8::Isolate* isolate, pointer_type const& obj) {
                                       destroy(isolate, Traits::template static_pointer_cast<T>(obj));
                                   }))
    {}

    class_(class_ const&)            = delete;
    class_& operator=(class_ const&) = delete;

    class_(class_&&)            = default;
    class_& operator=(class_&&) = delete;

    /// Find existing class_ to extend bindings
    static class_ extend(v8::Isolate* isolate) { return class_(isolate, detail::type_id<T>()); }

    template <typename ...Funcs>
    class_& ctor(Funcs&&... funcs)
    {
        std::tuple<Funcs...> funcs_tuple = std::make_tuple(std::forward<Funcs>(funcs)...);
        class_info_.set_ctor(
            [funcs_tuple = std::move(funcs_tuple)](v8::FunctionCallbackInfo<v8::Value> const& args) mutable {
            using indices = std::make_index_sequence<sizeof...(Funcs)>;
            return forward_overloaded_constructor<T>(args, funcs_tuple, indices{});
        });

        return *this;
    }

    /// Inhert from C++ class U
    template <typename U>
    class_& inherit()
    {
        static_assert(std::derived_from<T, U>, "Class U should be base for class T");
        // TODO: std::is_convertible<T*, U*> and check for duplicates in hierarchy?
        auto& base = detail::classes::find(isolate(), detail::type_id<U>());
        class_info_.set_base(base, [](pointer_type const& ptr) {
            return pointer_type{Traits::template static_pointer_cast<U>(Traits::template static_pointer_cast<T>(ptr))};
        });
        class_info_.js_function_template()->Inherit(base.js_function_template());
        return *this;
    }

    /// Enable new C++ objects auto-wrapping
    class_& auto_wrap_objects(bool auto_wrap = true)
    {
        class_info_.set_auto_wrap_objects(auto_wrap);
        return *this;
    }

    class_& only_reference_objects(bool only_ref = true)
    {
        class_info_.set_only_reference_objects(only_ref);
        return *this;
    }

    template <typename... Function>
    class_& member_function(std::string_view name, Function&&... funcs)
    {
        v8::HandleScope scope(isolate());

        v8::Local<v8::Name> v8_name = v8pp::to_v8(isolate(), name);
        v8::Local<v8::Data> wrapped_fun;

        wrapped_fun = wrap_member_function_template<T, Function...>(isolate(), std::forward<Function>(funcs)...);
        class_info_.js_function_template()->PrototypeTemplate()->Set(v8_name, wrapped_fun, v8::PropertyAttribute::None);
        return *this;
    }

    template <typename... Function>
    class_& static_function(std::string_view name, Function&&... funcs)
    {
        v8::HandleScope scope(isolate());

        v8::Local<v8::Name> v8_name = v8pp::to_v8(isolate(), name);
        v8::Local<v8::Data> wrapped_fun;

        wrapped_fun = wrap_static_function_template<Function...>(isolate(), std::forward<Function>(funcs)...);
        class_info_.js_function_template()->Set(v8_name, wrapped_fun, v8::PropertyAttribute::None);
        return *this;
    }

    /// Set read/write class property with getter and setter
    template <typename GetFunction, typename SetFunction = detail::none>
    class_& property(std::string_view name, GetFunction&& get, SetFunction&& set = {})
    {
        using Getter =
            typename std::conditional_t<std::is_member_function_pointer_v<GetFunction>,
                                        typename detail::function_traits<GetFunction>::template pointer_type<T>,
                                        typename std::decay_t<GetFunction>>;

        using Setter =
            typename std::conditional_t<std::is_member_function_pointer_v<SetFunction>,
                                        typename detail::function_traits<SetFunction>::template pointer_type<T>,
                                        typename std::decay_t<SetFunction>>;

        static_assert(std::is_member_function_pointer_v<GetFunction> || detail::is_callable<Getter>::value,
                      "GetFunction must be callable");
        static_assert(std::is_member_function_pointer_v<SetFunction> || detail::is_callable<Setter>::value ||
                          std::same_as<Setter, detail::none>,
                      "SetFunction must be callable");

        using GetClass = std::conditional_t<detail::function_with_object<Getter, T>, T, detail::none>;
        using SetClass = std::conditional_t<detail::function_with_object<Setter, T>, T, detail::none>;

        using property_type = v8pp::property<Getter, Setter, GetClass, SetClass>;

        v8::HandleScope scope(isolate());
        v8::Local<v8::String> v8_name = v8pp::to_v8(isolate(), name);

        v8::Local<v8::FunctionTemplate> getter_template =
            wrap_member_function_template<T, Getter>(isolate(), std::forward<Getter>(get));
        v8::Local<v8::FunctionTemplate> setter_template;
        if constexpr (!property_type::is_readonly)
        {
            setter_template = wrap_member_function_template<T, Setter>(isolate(), std::forward<Setter>(set));
        }

        class_info_.js_function_template()->PrototypeTemplate()->SetAccessorProperty(
            v8_name, getter_template, setter_template, v8::PropertyAttribute::DontDelete);
        return *this;
    }

    /// Set value as a read-only constant
    template <typename Value>
    class_& const_(std::string_view name, Value const& value)
    {
        v8::HandleScope scope(isolate());

        class_info_.js_function_template()->PrototypeTemplate()->Set(
            v8pp::to_v8(isolate(), name), to_v8(isolate(), value),
            v8::PropertyAttribute(v8::ReadOnly | v8::DontDelete));
        return *this;
    }

    /// Set value as a class static property
    template <typename Value>
    class_& static_(std::string_view const& name, Value const& value, bool readonly = false)
    {
        v8::HandleScope scope(isolate());

        class_info_.js_function_template()
            ->GetFunction(isolate()->GetCurrentContext())
            .ToLocalChecked()
            ->DefineOwnProperty(isolate()->GetCurrentContext(), v8pp::to_v8(isolate(), name), to_v8(isolate(), value),
                                v8::PropertyAttribute(v8::DontDelete | (readonly ? v8::ReadOnly : 0)))
            .FromJust();
        return *this;
    }

    /// v8::Isolate where the class bindings belongs
    v8::Isolate* isolate() { return class_info_.isolate(); }

    v8::Local<v8::FunctionTemplate> js_function_template() { return class_info_.js_function_template(); }

    /// Get wrapped object from V8 value, may return nullptr on fail.
    static object_pointer_type unwrap_object(v8::Isolate* isolate, v8::Local<v8::Value> value)
    {
        return Traits::template static_pointer_cast<T>(
            detail::classes::find(isolate, detail::type_id<T>()).unwrap_object(value));
    }

    /// Find V8 object handle for a wrapped C++ object, may return empty handle on fail
    /// or wrap the obj if class_.auto_wrap_objects()
    ///
    /// Modified to always wrap object
    static v8::Local<v8::Object> find_or_create_object(v8::Isolate* isolate, object_const_pointer_type const& obj)
    {
        auto& class_info = detail::classes::find(isolate, detail::type_id<T>(), detail::type_id(obj));
        v8::Local<v8::Object> wrapped_object = class_info.find_v8_object(Traits::const_pointer_cast(obj));
        if (wrapped_object.IsEmpty() && class_info.auto_wrap_objects())
        {
            wrapped_object = class_info.wrap_object(const_cast<object_pointer_type>(obj), 0);
        }

        return wrapped_object;
    }

    /// Destroy wrapped C++ object
    static void destroy_object(v8::Isolate* isolate, object_pointer_type const& obj)
    {
        detail::classes::find(isolate, detail::type_id<T>(), detail::type_id(obj))
            .remove_object(Traits::pointer_id(obj));
    }

    /// Destroy all wrapped C++ objects of this class
    static void destroy_objects(v8::Isolate* isolate)
    {
        detail::classes::find(isolate, detail::type_id<T>()).remove_objects();
    }

    /// Destroy all wrapped C++ objects and this binding class_
    static void destroy(v8::Isolate* isolate) { detail::classes::remove(isolate, detail::type_id<T>()); }

private:
    template <typename Attribute>
    static void member_get(v8::Local<v8::Name>, v8::PropertyCallbackInfo<v8::Value> const& info)
    {
        v8::Isolate* isolate = info.GetIsolate();

        try
        {
            auto self      = unwrap_object(isolate, info.This());
            Attribute attr = detail::external_data::get<Attribute>(info.Data());
            info.GetReturnValue().Set(to_v8(isolate, (*self).*attr));
        }
        catch (std::exception const& ex)
        {
            info.GetReturnValue().Set(throw_ex(isolate, ex.what()));
        }
    }

    template <typename Attribute>
    static void member_set(v8::Local<v8::Name>, v8::Local<v8::Value> value, v8::PropertyCallbackInfo<void> const& info)
    {
        v8::Isolate* isolate = info.GetIsolate();

        try
        {
            auto self       = unwrap_object(isolate, info.This());
            Attribute ptr   = detail::external_data::get<Attribute>(info.Data());
            using attr_type = typename detail::function_traits<Attribute>::return_type;
            (*self).*ptr    = v8pp::from_v8<attr_type>(isolate, value);
        }
        catch (std::exception const& ex)
        {
            if (info.ShouldThrowOnError())
            {
                isolate->ThrowException(throw_ex(isolate, ex.what()));
            }
            // TODO: info.GetReturnValue().Set(false);
        }
    }
};

void cleanup(v8::Isolate* isolate);

}  // namespace v8pp

#if V8PP_HEADER_ONLY
#    include "v8pp/class.cpp"
#endif
