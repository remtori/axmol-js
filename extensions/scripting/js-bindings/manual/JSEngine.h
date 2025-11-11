#pragma once

#include <optional>
#include <string_view>
#include <functional>
#include <v8.h>

#include "axmol/base/ScriptSupport.h"

#include "js-bindings/manual/js_isolate_data.h"
#include "js-bindings/manual/js_timers.h"

namespace ax
{

class EventListenerCustom;

class JSEngine : public ScriptEngineProtocol
{
public:
    static JSEngine* fromIsolate(v8::Isolate* isolate);

    JSEngine();
    virtual ~JSEngine();

    bool init();
    void cleanup();

    virtual ccScriptType getScriptType() override { return kScriptTypeJS; };

    int executeString(const char* codes) override;
    int executeScriptFile(const char* filename) override;
    int executeGlobalFunction(const char* functionName) override;

    int sendEvent(const ScriptEvent& evt) override;
    bool handleAssert(const char* msg) override;
    bool parseConfig(ConfigType type, std::string_view str) override;

    void rootObject(Object* obj) override;
    void unrootObject(Object* obj) override;
    void removeObjectProxy(Object* obj) override;
    void removeScriptObjectByObject(Object* obj) override;
    void garbageCollect() override;

    JsTimers& jsTimers() { return _timers; }

    const IsolateData& ext()
    {
        AXASSERT(_isolateData != std::nullopt, "IsolateData is null");
        return *_isolateData;
    }

    IsolateData& mutable_ext()
    {
        AXASSERT(_isolateData != std::nullopt, "IsolateData is null");
        return *_isolateData;
    }

    v8::Local<v8::Object> callsitePrototype() const { return _callsitePrototype.Get(_isolate); }
    void evalWithOrigin(std::string_view origin, std::string_view code);
    std::string_view currentEvalOrigin() const { return _currentEvalOrigin; }

    static void reportException(v8::Isolate* isolate, const v8::TryCatch&);
    static void reportException(v8::Isolate* isolate, v8::Local<v8::Message> message, v8::Local<v8::Value> data);

private:
    int handleNodeEvent(const BasicScriptData&);

    void update(float dt);

private:
    JsTimers _timers;
    std::optional<IsolateData> _isolateData;
    ax::EventListenerCustom* _directorResetListener;

    v8::Isolate* _isolate;
    v8::Global<v8::Context> _context;
    v8::Global<v8::Object> _globalObject;
    v8::Global<v8::Function> _eventLoopTickFn;
    v8::Global<v8::Object> _callsitePrototype;

    std::string_view _currentEvalOrigin;
};
}  // namespace ax
