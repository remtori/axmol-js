#pragma once

#include <v8-local-handle.h>
#include <v8-template.h>
#include <string_view>
#include <unordered_map>

#include "axmol/base/Logging.h"

#include "v8pp/module.hpp"
#include "v8pp/class.hpp"

class JsRegistry
{
public:
    JsRegistry(v8::Isolate* isolate) : _isolate(isolate) {}

    v8::Isolate* isolate() const { return _isolate; }

    v8pp::module& module(std::string_view name)
    {
        auto it = _registry.find(name);
        if (it == _registry.end())
        {
            AXLOGI("[JS] registering namespace: {}", name);
            it = _registry.emplace(name, v8pp::module(_isolate)).first;
        }

        return it->second;
    }

    v8::Local<v8::ObjectTemplate> getAllAsObjectTemplate()
    {
        v8::EscapableHandleScope scope(_isolate);

        v8pp::module main(_isolate);
        for (auto& [name, mod] : _registry)
        {
            main.submodule(name, mod);
        }

        return scope.Escape(main.impl());
    }

    v8::Local<v8::Object> getAllAsObject()
    {
        v8::EscapableHandleScope scope(_isolate);

        v8pp::module main(_isolate);
        for (auto& [name, mod] : _registry)
        {
            main.submodule(name, mod);
        }

        return scope.Escape(main.new_instance());
    }

private:
    v8::Isolate* _isolate;
    std::unordered_map<std::string_view, v8pp::module> _registry;
};
