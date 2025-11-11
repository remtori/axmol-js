#pragma once

#include "axmol/base/Object.h"
#include "axmol/base/Macros.h"

#include "type_info.hpp"

namespace v8pp
{

template <typename T>
struct convert;

struct object_ptr_traits
{
    using pointer_type       = void*;
    using const_pointer_type = const void*;

    template <typename T>
    using object_pointer_type = T*;
    template <typename T>
    using object_const_pointer_type = const T*;

    using object_id = void*;

    static object_id pointer_id(void* ptr) { return ptr; }
    static pointer_type key(object_id id) { return static_cast<pointer_type>(id); }
    static pointer_type const_pointer_cast(const_pointer_type ptr) { return const_cast<void*>(ptr); }
    template <typename T, typename U>
    static T* static_pointer_cast(U* ptr)
    {
        return static_cast<T*>(ptr);
    }

    template <typename T>
    using convert_ptr = convert<T*>;

    template <typename T>
    using convert_ref = convert<T&>;

    template <typename T, typename... Args>
    static object_pointer_type<T> create(Args&&... args)
    {
        return new T(std::forward<Args>(args)...);
    }

    template <typename T>
    static void destroy(object_pointer_type<T> const& ptr)
        requires(std::is_base_of_v<ax::Object, T>)
    {
        if (ptr->getReferenceCount() == 0)
        {
            AXLOGE("ptr->getReferenceCount() == 0, {}", detail::type_id<T>().name());
        }

        // AXLOGI("LIFE Release: {}", ptr->_ID);
        ptr->release();
    }

    template <typename T>
    static void destroy(object_pointer_type<T> const& ptr)
        requires(!std::is_base_of_v<ax::Object, T>)
    {
        delete ptr;
    }

    template <typename T>
    static size_t object_size(object_pointer_type<T> const&)
    {
        return sizeof(T);
    }
};

}  // namespace v8pp
