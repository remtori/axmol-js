#include "js-bindings/bindings/axjs_audioengine_auto.hpp"
#if defined(AX_ENABLE_AUDIO) &&                                                                                                     \
    (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID || AX_TARGET_PLATFORM == AX_PLATFORM_IOS || AX_TARGET_PLATFORM == AX_PLATFORM_MAC || \
     defined(_WIN32) || AX_TARGET_PLATFORM == AX_PLATFORM_LINUX || AX_TARGET_PLATFORM == AX_PLATFORM_WASM)
#    include "axmol/audio/AudioEngine.h"
#    include "js-bindings/manual/JSConversions.h"
static void js_register_ax_audioengine_AudioProfile(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::AudioProfile> class_AudioProfile(isolate);
    class_AudioProfile.ctor([]() { return new ax::AudioProfile(); }).auto_wrap_objects(true);
    mod.class_("AudioProfile", class_AudioProfile);
}
static void js_register_ax_audioengine_AudioEngine(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::AudioEngine> class_AudioEngine(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_AudioEngine.static_function("lazyInit", &ax::AudioEngine::lazyInit)
        .static_function("end", &ax::AudioEngine::end)
        .static_function("getDefaultProfile", &ax::AudioEngine::getDefaultProfile)
        .static_function(
            "play2d",
            [](std::string_view arg0, ax::AudioPlayerSettings arg1) { return ax::AudioEngine::play2d(arg0, arg1); },
            [](std::string_view arg0, ax::AudioPlayerSettings arg1, const ax::AudioProfile* arg2)
            { return ax::AudioEngine::play2d(arg0, arg1, arg2); },
            [](std::string_view arg0) { return ax::AudioEngine::play2d(arg0); },
            [](std::string_view arg0, bool arg1) { return ax::AudioEngine::play2d(arg0, arg1); },
            [](std::string_view arg0, bool arg1, float arg2) { return ax::AudioEngine::play2d(arg0, arg1, arg2); },
            [](std::string_view arg0, bool arg1, float arg2, const ax::AudioProfile* arg3)
            { return ax::AudioEngine::play2d(arg0, arg1, arg2, arg3); })
        .static_function(
            "play3d",
            [](std::string_view arg0, ax::AudioPlayerSettings arg1) { return ax::AudioEngine::play3d(arg0, arg1); },
            [](std::string_view arg0, ax::AudioPlayerSettings arg1, const ax::AudioProfile* arg2)
            { return ax::AudioEngine::play3d(arg0, arg1, arg2); },
            [](std::string_view arg0, ax::Vec3 arg1) { return ax::AudioEngine::play3d(arg0, arg1); },
            [](std::string_view arg0, ax::Vec3 arg1, bool arg2) { return ax::AudioEngine::play3d(arg0, arg1, arg2); },
            [](std::string_view arg0, ax::Vec3 arg1, bool arg2, float arg3) { return ax::AudioEngine::play3d(arg0, arg1, arg2, arg3); },
            [](std::string_view arg0, ax::Vec3 arg1, bool arg2, float arg3, const ax::AudioProfile* arg4)
            { return ax::AudioEngine::play3d(arg0, arg1, arg2, arg3, arg4); })
        .static_function("setLoop", &ax::AudioEngine::setLoop)
        .static_function("isLoop", &ax::AudioEngine::isLoop)
        .static_function("setVolume", &ax::AudioEngine::setVolume)
        .static_function("getVolume", &ax::AudioEngine::getVolume)
        .static_function("setPitch", &ax::AudioEngine::setPitch)
        .static_function("getPitch", &ax::AudioEngine::getPitch)
        .static_function("pause", &ax::AudioEngine::pause)
        .static_function("pauseAll", &ax::AudioEngine::pauseAll)
        .static_function("resume", &ax::AudioEngine::resume)
        .static_function("resumeAll", &ax::AudioEngine::resumeAll)
        .static_function("stop", &ax::AudioEngine::stop)
        .static_function("stopAll", &ax::AudioEngine::stopAll)
        .static_function("setCurrentTime", &ax::AudioEngine::setCurrentTime)
        .static_function("getCurrentTime", &ax::AudioEngine::getCurrentTime)
        .static_function("getDuration", &ax::AudioEngine::getDuration)
        .static_function("getState", &ax::AudioEngine::getState)
        .static_function("getMaxAudioInstance", &ax::AudioEngine::getMaxAudioInstance)
        .static_function("setMaxAudioInstance", &ax::AudioEngine::setMaxAudioInstance)
        .static_function("uncache", &ax::AudioEngine::uncache)
        .static_function("uncacheAll", &ax::AudioEngine::uncacheAll)
        .static_function(
            "getProfile",
            [](std::string_view arg0) { return ax::AudioEngine::getProfile(arg0); },
            [](int arg0) { return ax::AudioEngine::getProfile(arg0); })
        .static_function(
            "preload",
            [](std::string_view arg0, std::function<void(bool)> arg1) { ax::AudioEngine::preload(arg0, arg1); },
            [](std::string_view arg0) { ax::AudioEngine::preload(arg0); })
        .static_function("getPlayingAudioCount", &ax::AudioEngine::getPlayingAudioCount)
        .static_function("setEnabled", &ax::AudioEngine::setEnabled)
        .static_function("isEnabled", &ax::AudioEngine::isEnabled)
        .static_function(
            "setPan",
            [](int arg0, float arg1) { ax::AudioEngine::setPan(arg0, arg1); },
            [](int arg0, float arg1, float arg2) { ax::AudioEngine::setPan(arg0, arg1, arg2); })
        .static_function("getPan", &ax::AudioEngine::getPan)
        .static_function("getSourcePosition", &ax::AudioEngine::getSourcePosition)
        .static_function("setSourcePosition", &ax::AudioEngine::setSourcePosition)
        .static_function("setListenerPosition", &ax::AudioEngine::setListenerPosition)
        .static_function("getListenerPosition", &ax::AudioEngine::getListenerPosition)
        .static_function("setDistanceScale", &ax::AudioEngine::setDistanceScale)
        .static_function("getDistanceScale", &ax::AudioEngine::getDistanceScale)
        .static_function("setReverbProperties", &ax::AudioEngine::setReverbProperties)
        .auto_wrap_objects(true);
    mod.class_("AudioEngine", class_AudioEngine);
}
void js_register_all_ax_audioengine(JsRegistry& registry)
{
    v8pp::module& mod = registry.module("ax");
    js_register_ax_audioengine_AudioProfile(mod);
    js_register_ax_audioengine_AudioEngine(mod);
}
#endif
