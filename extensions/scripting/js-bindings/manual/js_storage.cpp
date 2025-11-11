#include "js_storage.h"

#include <string>
#include <string_view>
#include <tsl/robin_map.h>

#include "axmol/base/UserDefault.h"
#include "v8pp/class.hpp"

namespace
{

class SessionStorage
{
public:
    void setItem(std::string key, std::string value) { _storage.insert_or_assign(std::move(key), std::move(value)); }

    std::string_view getItem(const std::string& key) const
    {
        auto it = _storage.find(key);
        if (it == _storage.end())
        {
            return {};
        }

        return it->second;
    }

    void removeItem(const std::string& key) { _storage.erase(key); }

    size_t length() const { return _storage.size(); }

    void clear() { _storage.clear(); }

private:
    tsl::robin_map<std::string, std::string> _storage;
};

class LocalStorage : public ax::UserDefault
{
public:
    LocalStorage(std::string_view name)
    {
        ax::UserDefault::setFileName(name);
        this->lazyInit();

        ax::UserDefault::setFileName();
    }

    void setItem(const std::string& key, std::string value) { this->setStringForKey(key.c_str(), std::move(value)); }

    std::string_view getItem(const std::string& key) { return this->getStringForKey(key.c_str()); }

    void removeItem(const std::string& key) { this->deleteValueForKey(key.c_str()); }

    size_t length() const { return _values.size(); }

    void clear()
    {
        _values.clear();
        flush();
    }
};

}  // namespace

void js_bind_ops_storage(v8pp::module& mod)
{
    {
        v8pp::class_<SessionStorage> clazz(mod.isolate(), [](v8::Isolate*, auto*) {});
        clazz.member_function("setItem", &SessionStorage::setItem)
            .member_function("getItem", &SessionStorage::getItem)
            .member_function("removeItem", &SessionStorage::removeItem)
            .member_function("length", &SessionStorage::length)
            .member_function("clear", &SessionStorage::clear)
            .auto_wrap_objects(true);

        clazz.js_function_template()->SetClassName(v8pp::to_v8(mod.isolate(), "SessionStorage"));
    }

    static SessionStorage sessionStorage;
    mod.function("op_get_session_storage", []() { return &sessionStorage; });

    {
        v8pp::class_<LocalStorage> clazz(mod.isolate(), [](v8::Isolate*, LocalStorage* self) { delete self; });

        clazz.member_function("setItem", &LocalStorage::setItem)
            .member_function("getItem", &LocalStorage::getItem)
            .member_function("removeItem", &LocalStorage::removeItem)
            .member_function("length", &LocalStorage::length)
            .member_function("clear", &LocalStorage::clear)
            .auto_wrap_objects(true);
        clazz.js_function_template()->SetClassName(v8pp::to_v8(mod.isolate(), "LocalStorage"));
    }

    mod.function("op_create_local_storage", [](std::string_view name) { return new LocalStorage(name); });
}
