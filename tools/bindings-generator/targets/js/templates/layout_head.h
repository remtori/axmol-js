\#pragma once

\#include "axmol/base/Config.h"
\#include "js-bindings/manual/js_registry.h"

#if $macro_judgement
$macro_judgement
#end if

void js_register_all_${prefix}(JsRegistry&);
