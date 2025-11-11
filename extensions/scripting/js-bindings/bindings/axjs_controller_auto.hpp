#pragma once
#include "axmol/base/Config.h"
#include "js-bindings/manual/js_registry.h"
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID || AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
void js_register_all_ax_controller(JsRegistry&);
#endif  // #if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID || AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
