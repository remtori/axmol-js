#include "js-bindings/bindings/axjs_video_auto.hpp"
#if defined(AX_ENABLE_MEDIA)
#    include "axmol/ui/UIMediaPlayer.h"
#    include "js-bindings/manual/JSConversions.h"
static void js_register_ax_video_MediaPlayer(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::MediaPlayer> class_MediaPlayer(isolate);
    class_MediaPlayer.ctor([]() { return new ax::ui::MediaPlayer(); })
        .template inherit<ax::ui::Widget>()
        .member_function("setFileName", &ax::ui::MediaPlayer::setFileName)
        .member_function("getFileName", &ax::ui::MediaPlayer::getFileName)
        .member_function("setURL", &ax::ui::MediaPlayer::setURL)
        .member_function("getURL", &ax::ui::MediaPlayer::getURL)
        .member_function("setLooping", &ax::ui::MediaPlayer::setLooping)
        .member_function("setUserInputEnabled", &ax::ui::MediaPlayer::setUserInputEnabled)
        .member_function("setStyle", &ax::ui::MediaPlayer::setStyle)
        .member_function("setPlayRate", &ax::ui::MediaPlayer::setPlayRate)
        .member_function("play", &ax::ui::MediaPlayer::play)
        .member_function("pausePlayback", &ax::ui::MediaPlayer::pausePlayback)
        .member_function("resumePlayback", &ax::ui::MediaPlayer::resumePlayback)
        .member_function("stop", &ax::ui::MediaPlayer::stop)
        .member_function("seekTo", &ax::ui::MediaPlayer::seekTo)
        .member_function("getCurrentTime", &ax::ui::MediaPlayer::getCurrentTime)
        .member_function("getDuration", &ax::ui::MediaPlayer::getDuration)
        .member_function("isPlaying", &ax::ui::MediaPlayer::isPlaying)
        .member_function("isLooping", &ax::ui::MediaPlayer::isLooping)
        .member_function("isUserInputEnabled", &ax::ui::MediaPlayer::isUserInputEnabled)
        .member_function("setKeepAspectRatioEnabled", &ax::ui::MediaPlayer::setKeepAspectRatioEnabled)
        .member_function("isKeepAspectRatioEnabled", &ax::ui::MediaPlayer::isKeepAspectRatioEnabled)
        .member_function("setFullScreenEnabled", &ax::ui::MediaPlayer::setFullScreenEnabled)
        .member_function("isFullScreenEnabled", &ax::ui::MediaPlayer::isFullScreenEnabled)
        .member_function("onPlayEvent", &ax::ui::MediaPlayer::onPlayEvent)
        .member_function("getState", &ax::ui::MediaPlayer::getState)
        .member_function("setMediaController", &ax::ui::MediaPlayer::setMediaController)
        .member_function("getMediaController", &ax::ui::MediaPlayer::getMediaController)
        .static_function("create", &ax::ui::MediaPlayer::create)
        .auto_wrap_objects(true);
    mod.class_("MediaPlayer", class_MediaPlayer);
}
void js_register_all_ax_video(JsRegistry& registry)
{
    v8pp::module& mod = registry.module("axui");
    js_register_ax_video_MediaPlayer(mod);
}
#endif
