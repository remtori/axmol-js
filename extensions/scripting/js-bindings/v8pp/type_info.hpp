#pragma once

#include <string_view>
#include <type_traits>

namespace v8pp::detail
{

/// Type information for custom RTTI
class type_info
{
public:
    constexpr std::string_view name() const { return name_; }
    constexpr bool operator==(type_info const& other) const { return name_ == other.name_; }
    constexpr bool operator!=(type_info const& other) const { return name_ != other.name_; }

private:
    template <typename T>
    constexpr friend type_info type_id();

    template <typename T>
        requires(std::is_pointer_v<T>)
    friend type_info type_id(T value);

    constexpr explicit type_info(std::string_view name) : name_(name) {}

    std::string_view name_;
};

/// Get type information for type T
/// The idea is borrowed from https://github.com/Manu343726/ctti
template <typename T>
constexpr type_info type_id()
{
    using enforced_type = std::remove_cvref_t<std::remove_pointer_t<T>>;

    return type_info(typeid(enforced_type&).name());
}

template <typename T>
    requires(std::is_pointer_v<T>)
type_info type_id(T value)
{
    using class_type = std::remove_cvref_t<std::remove_pointer_t<T>>;
    if (value == nullptr)
        return type_id<T>();

    return type_info(typeid(const_cast<class_type&>(*static_cast<const class_type*>(value))).name());
}

}  // namespace v8pp::detail
