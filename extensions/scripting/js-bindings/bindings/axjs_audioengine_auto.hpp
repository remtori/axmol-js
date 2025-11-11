#pragma once
#include "axmol/base/Config.h"
#include "js-bindings/manual/js_registry.h"
#if defined(AX_ENABLE_AUDIO) &&                                                                                                     \
    (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID || AX_TARGET_PLATFORM == AX_PLATFORM_IOS || AX_TARGET_PLATFORM == AX_PLATFORM_MAC || \
     defined(_WIN32) || AX_TARGET_PLATFORM == AX_PLATFORM_LINUX || AX_TARGET_PLATFORM == AX_PLATFORM_WASM)
void js_register_all_ax_audioengine(JsRegistry&);
#endif  // #if defined(AX_ENABLE_AUDIO) && (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID || AX_TARGET_PLATFORM == AX_PLATFORM_IOS ||
        // AX_TARGET_PLATFORM == AX_PLATFORM_MAC || defined(_WIN32) || AX_TARGET_PLATFORM == AX_PLATFORM_LINUX || AX_TARGET_PLATFORM ==
        // AX_PLATFORM_WASM)
