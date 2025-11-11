#pragma once

#include <type_traits>
#include <functional>
#include <tuple>

#include "v8pp/function.hpp"

namespace v8pp
{

namespace detail
{

template <typename Func, bool with_class_instance = false>
constexpr bool can_call_with_args(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    using FTraits                   = function_traits<Func>;
    constexpr bool with_isolate     = is_first_arg_isolate<Func, with_class_instance>;
    constexpr bool with_direct_args = is_direct_args<Func, with_isolate + with_class_instance>;

    if constexpr (with_direct_args)
    {
        return true;
    }

    constexpr size_t offset    = size_t(with_class_instance) + size_t(with_isolate);
    constexpr size_t arg_count = std::tuple_size_v<typename FTraits::arguments> - offset;
    return args.Length() == arg_count;
}

template <typename Func, bool ignore_ex = true>
bool try_call(Func&& func, const v8::FunctionCallbackInfo<v8::Value>& args)
{
    using FTraits = function_traits<Func>;
    if (!can_call_with_args<Func>(args))
    {
        return false;
    }

    try
    {
        if constexpr (std::is_same_v<typename FTraits::return_type, void>)
        {
            call_from_v8<v8pp::object_ptr_traits>(std::forward<Func>(func), args);
        }
        else
        {
            auto ret    = call_from_v8<v8pp::object_ptr_traits>(std::forward<Func>(func), args);
            auto v8_ret = v8pp::to_v8(args.GetIsolate(), ret);
            args.GetReturnValue().Set(v8_ret);
        }

        return true;
    }
    catch (const std::exception&)
    {
        if constexpr (ignore_ex)
            return false;
        else
            throw;
    }
}

template <typename Clazz, typename Func, size_t... Indices>
void call_from_v8_instance(Func&& func,
                           v8::FunctionCallbackInfo<v8::Value> const& args,
                           Clazz* instance,
                           std::index_sequence<Indices...>)
{
    using FTraits = function_traits<Func>;

    constexpr bool with_isolate = is_first_arg_isolate<Func, 1>;
    if constexpr (is_direct_args<Func, with_isolate + 1>)
    {
        if constexpr (with_isolate)
        {
            std::invoke(func, instance, args.GetIsolate(), args);
        }
        else
        {
            std::invoke(func, instance, args);
        }
    }
    else if constexpr (std::is_same_v<typename FTraits::return_type, void>)
    {
        std::invoke(func, instance,
                    v8pp::from_v8<typename std::tuple_element<Indices + 1, typename FTraits::arguments>::type>(
                        args.GetIsolate(), args[Indices])...);
    }
    else
    {
        auto ret =
            std::invoke(func, instance,
                        v8pp::from_v8<typename std::tuple_element<Indices + 1, typename FTraits::arguments>::type>(
                            args.GetIsolate(), args[Indices])...);

        auto v8_ret = v8pp::to_v8(args.GetIsolate(), ret);
        args.GetReturnValue().Set(v8_ret);
    }
}

template <typename Clazz, typename Func, bool ignore_ex = true>
bool try_call_instance(Func&& func, Clazz* instance, const v8::FunctionCallbackInfo<v8::Value>& args)
{
    if (!can_call_with_args<Func, true>(args))
    {
        return false;
    }

    try
    {
        using FTraits = function_traits<Func>;
        using indices = std::make_index_sequence<std::tuple_size_v<typename FTraits::arguments> - 1>;
        call_from_v8_instance(std::forward<Func>(func), args, instance, indices{});

        return true;
    }
    catch (const std::exception&)
    {
        if constexpr (ignore_ex)
            return false;
        else
            throw;
    }
}

template <typename Clazz, typename Func>
bool try_call_constructor(Func&& func, const v8::FunctionCallbackInfo<v8::Value>& args, Clazz** ret)
{
    try
    {
        *ret = call_from_v8<v8pp::object_ptr_traits>(std::forward<Func>(func), args);
        return true;
    }
    catch (const std::exception& e)
    {
        return false;
    }
}

template <typename Clazz, typename Func>
bool try_call_zero_arg_constructor(Func&& func, Clazz** ret)
{
    using FTraits = function_traits<Func>;
    if constexpr (std::tuple_size_v<typename FTraits::arguments> == 0)
    {
        try
        {
            *ret = std::invoke(func);
            return true;
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    return false;
}

template <typename Clazz, typename... Function, size_t... Indices>
void forward_member_function_impl(const v8::FunctionCallbackInfo<v8::Value>& args, std::index_sequence<Indices...>)
{
    Clazz* instance = class_<Clazz, v8pp::object_ptr_traits>::unwrap_object(args.GetIsolate(), args.This());
    if (!instance)
    {
        args.GetIsolate()->ThrowException(v8::Exception::TypeError(
            v8::String::NewFromUtf8(args.GetIsolate(), "Invalid native object").ToLocalChecked()));

        return;
    }

    auto& funcs = external_data::get<std::tuple<Function...>>(args.Data());

    constexpr size_t overload_count = sizeof...(Function);
    if constexpr (overload_count == 1)
    {
        try
        {
            (try_call_instance<Clazz, Function, false>(std::forward<Function>(std::get<Indices>(funcs)), instance,
                                                       args),
             ...);
        }
        catch (std::exception& e)
        {
            args.GetIsolate()->ThrowException(
                v8::Exception::TypeError(v8::String::NewFromUtf8(args.GetIsolate(), e.what()).ToLocalChecked()));
        }

        return;
    }

    bool ok = (try_call_instance<Clazz>(std::forward<Function>(std::get<Indices>(funcs)), instance, args) || ...);
    if (!ok)
    {
        args.GetIsolate()->ThrowException(v8::Exception::TypeError(
            v8::String::NewFromUtf8(args.GetIsolate(), "No matching overload found for the given arguments")
                .ToLocalChecked()));
    }
}

template <typename Clazz, typename... Function>
void forward_member_function(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    using indices = std::make_index_sequence<sizeof...(Function)>;
    forward_member_function_impl<Clazz, Function...>(args, indices{});
}

template <typename... Function, size_t... Indices>
void forward_static_function_impl(const v8::FunctionCallbackInfo<v8::Value>& args, std::index_sequence<Indices...>)
{
    auto& funcs = external_data::get<std::tuple<Function...>>(args.Data());

    constexpr size_t overload_count = sizeof...(Function);
    if constexpr (overload_count == 1)
    {
        try
        {
            (try_call<Function, false>(std::forward<Function>(std::get<Indices>(funcs)), args), ...);
        }
        catch (std::exception& e)
        {
            args.GetIsolate()->ThrowException(
                v8::Exception::TypeError(v8::String::NewFromUtf8(args.GetIsolate(), e.what()).ToLocalChecked()));
        }

        return;
    }

    bool ok = (try_call<Function>(std::forward<Function>(std::get<Indices>(funcs)), args) || ...);
    if (!ok)
    {
        args.GetIsolate()->ThrowException(v8::Exception::TypeError(
            v8::String::NewFromUtf8(args.GetIsolate(), "No matching overload found for the given arguments")
                .ToLocalChecked()));
    }
}

template <typename... Function>
void forward_static_function(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    using indices = std::make_index_sequence<sizeof...(Function)>;
    forward_static_function_impl<Function...>(args, indices{});
}

}  // namespace detail

template <typename Clazz, typename... Function>
v8::Local<v8::FunctionTemplate> wrap_member_function_template(v8::Isolate* isolate, Function&&... funcs)
{
    auto funcsTuple = std::make_tuple(std::forward<Function>(funcs)...);
    return v8::FunctionTemplate::New(isolate, &detail::forward_member_function<Clazz, Function...>,
                                     detail::external_data::set(isolate, std::move(funcsTuple)));
}

template <typename... Function>
v8::Local<v8::FunctionTemplate> wrap_static_function_template(v8::Isolate* isolate, Function&&... funcs)
{
    auto funcsTuple = std::make_tuple(std::forward<Function>(funcs)...);
    return v8::FunctionTemplate::New(isolate, &detail::forward_static_function<Function...>,
                                     detail::external_data::set(isolate, std::move(funcsTuple)));
}

template <typename Clazz, typename... Function, size_t... Indices>
std::pair<Clazz*, size_t> forward_overloaded_constructor(v8::FunctionCallbackInfo<v8::Value> const& args,
                                                         std::tuple<Function...>& funcs,
                                                         std::index_sequence<Indices...>)
{
    Clazz* ret = nullptr;
    bool ok =
        (detail::try_call_constructor<Clazz>(std::forward<Function>(std::get<Indices>(funcs)), args, &ret) || ...);

    if (!ok)
    {
        ok = (detail::try_call_zero_arg_constructor<Clazz>(std::forward<Function>(std::get<Indices>(funcs)), &ret) ||
              ...);
    }

    if (!ok)
    {
        throw std::runtime_error("No matching overload found for the given arguments");
    }

    return std::make_pair(ret, sizeof(Clazz));
}

}  // namespace v8pp