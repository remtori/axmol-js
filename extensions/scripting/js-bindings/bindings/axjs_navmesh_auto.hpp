#pragma once
#include "axmol/base/Config.h"
#include "js-bindings/manual/js_registry.h"
#if defined(AX_ENABLE_NAVMESH)
void js_register_all_ax_navmesh(JsRegistry&);
#endif  // #if defined(AX_ENABLE_NAVMESH)
