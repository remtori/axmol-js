#pragma once
#include "axmol/base/Config.h"
#include "js-bindings/manual/js_registry.h"
#if defined(AX_ENABLE_3D)
void js_register_all_ax_3d(JsRegistry&);
#endif  // #if defined(AX_ENABLE_3D)
