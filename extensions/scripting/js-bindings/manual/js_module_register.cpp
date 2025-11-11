#include "js-bindings/manual/js_module_register.h"

#include "js-bindings/bindings/axjs_audioengine_auto.hpp"
#include "js-bindings/bindings/axjs_base_auto.hpp"
#include "js-bindings/bindings/axjs_controller_auto.hpp"
#include "js-bindings/bindings/axjs_csloader_auto.hpp"
#include "js-bindings/bindings/axjs_extension_auto.hpp"
#include "js-bindings/bindings/axjs_spine_auto.hpp"
#include "js-bindings/bindings/axjs_studio_auto.hpp"
#include "js-bindings/bindings/axjs_ui_auto.hpp"
#include "js-bindings/bindings/axjs_video_auto.hpp"
#include "js-bindings/bindings/axjs_webview_auto.hpp"

#include "v8pp/class.hpp"
#include "cocostudio/CocoStudio.h"

namespace
{
/**
 * Register all base virtual class that other Classes inherit from
 */
void js_register_all_dummy_classes(JsRegistry& registry)
{
    v8pp::class_<cocostudio::ProcessBase> cocostudio_ProcessBase(registry.isolate());
}
}  // namespace

int js_module_register(JsRegistry& registry)
{
    js_register_all_ax_base(registry);
    js_register_all_dummy_classes(registry);

    js_register_all_ax_spine(registry);
    js_register_all_ax_csloader(registry);
    js_register_all_ax_extension(registry);
    js_register_all_ax_studio(registry);
    js_register_all_ax_ui(registry);
    js_register_all_ax_webview(registry);

#if defined(AX_ENABLE_AUDIO)
    js_register_all_ax_audioengine(registry);
#endif

#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID || AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
    js_register_all_ax_controller(registry);
#endif

#if defined(AX_ENABLE_MEDIA)
    js_register_all_ax_video(registry);
#endif

    return 1;
}
