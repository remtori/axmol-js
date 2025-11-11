#pragma once
// PER_ISOLATE_* macros: We have a lot of per-isolate properties
// and adding and maintaining their getters and setters by hand would be
// difficult so let's make the preprocessor generate them for us.
//
// In each macro, `V` is expected to be the name of a macro or function which
// accepts the number of arguments provided in each tuple in the macro body,
// typically two. The named function will be invoked against each tuple.
//
// Make sure that any macro V defined for use with the PER_ISOLATE_* macros is
// undefined again after use.

// Private symbols are per-isolate primitives but Environment proxies them
// for the sake of convenience.  Strings should be ASCII-only and have a
// "axmol:" prefix.
#define PER_ISOLATE_SYMBOL_PROPERTIES(V)                             \
    V(dispatch_node_event_private_symbol, "axmol:dispatchNodeEvent") \
    V(function_callback_private_symbol, "axmol::functionCallback")

#define PER_ISOLATE_STRING_PROPERTIES(V)                 \
    V(x_string, "x")                                     \
    V(y_string, "y")                                     \
    V(z_string, "z")                                     \
    V(w_string, "w")                                     \
    V(h_string, "h")                                     \
    V(r_string, "r")                                     \
    V(g_string, "g")                                     \
    V(b_string, "b")                                     \
    V(a_string, "a")                                     \
    V(c_string, "c")                                     \
    V(d_string, "d")                                     \
    V(m_string, "m")                                     \
    V(s_string, "s")                                     \
    V(v_string, "v")                                     \
    V(tx_string, "tx")                                   \
    V(ty_string, "ty")                                   \
    V(data_string, "data")                               \
    V(begin_string, "begin")                             \
    V(end_string, "end")                                 \
    V(duration_string, "duration")                       \
    V(alphaBits_string, "alphaBits")                     \
    V(blueBits_string, "blueBits")                       \
    V(bottom_string, "bottom")                           \
    V(compressed_string, "compressed")                   \
    V(coneAngle_string, "coneAngle")                     \
    V(coneOffset_string, "coneOffset")                   \
    V(decorated_string, "decorated")                     \
    V(density_string, "density")                         \
    V(depthBits_string, "depthBits")                     \
    V(downloadState_string, "downloadState")             \
    V(dst_string, "dst")                                 \
    V(edgeBias_string, "edgeBias")                       \
    V(endIndex_string, "endIndex")                       \
    V(endPosition_string, "endPosition")                 \
    V(file_string, "file")                               \
    V(fourccId_string, "fourccId")                       \
    V(fragStage_string, "fragStage")                     \
    V(friction_string, "friction")                       \
    V(greenBits_string, "greenBits")                     \
    V(height_string, "height")                           \
    V(innerHeight_string, "innerHeight")                 \
    V(innerRadius_string, "innerRadius")                 \
    V(innerWidth_string, "innerWidth")                   \
    V(left_string, "left")                               \
    V(location_string, "location")                       \
    V(md5_string, "md5")                                 \
    V(multisamplingCount_string, "multisamplingCount")   \
    V(name_string, "name")                               \
    V(offset_string, "offset")                           \
    V(ops_string, "ops")                                 \
    V(outerHeight_string, "outerHeight")                 \
    V(outerRadius_string, "outerRadius")                 \
    V(outerWidth_string, "outerWidth")                   \
    V(params_string, "params")                           \
    V(path_string, "path")                               \
    V(plist_string, "plist")                             \
    V(points_string, "points")                           \
    V(redBits_string, "redBits")                         \
    V(restitution_string, "restitution")                 \
    V(right_string, "right")                             \
    V(size_string, "size")                               \
    V(src_string, "src")                                 \
    V(startIndex_string, "startIndex")                   \
    V(startPosition_string, "startPosition")             \
    V(stencilBits_string, "stencilBits")                 \
    V(tag_string, "tag")                                 \
    V(timestamp_string, "timestamp")                     \
    V(top_string, "top")                                 \
    V(type_string, "type")                               \
    V(update_string, "update")                           \
    V(vertStage_string, "vertStage")                     \
    V(vertexAttrib_string, "vertexAttrib")               \
    V(visible_string, "visible")                         \
    V(vsync_string, "vsync")                             \
    V(width_string, "width")                             \
    V(__bindings_string, "__bindings")                   \
    V(__bootstrap_string, "__bootstrap")                 \
    V(_ctor, "_ctor")                                    \
    V(external, "external")                              \
    V(heap_total, "heapTotal")                           \
    V(heap_used, "heapUsed")                             \
    V(physical_total, "physicalTotal")                   \
    V(prototype, "prototype")                            \
    V(on_key_pressed_string, "_onKeyPressed")            \
    V(on_key_released_string, "_onKeyReleased")          \
    V(on_mouse_down_string, "_onMouseDown")              \
    V(on_mouse_up_string, "onMouseUp")                   \
    V(on_mouse_move_string, "_onMouseMove")              \
    V(on_mouse_scroll_string, "onMouseScroll")           \
    V(on_touches_began_string, "onTouchesBegan")         \
    V(on_touches_moved_string, "onTouchesMoved")         \
    V(on_touches_ended_string, "onTouchesEnded")         \
    V(on_touches_cancelled_string, "onTouchesCancelled") \
    V(on_touch_began_string, "onTouchBegan")             \
    V(on_touch_moved_string, "onTouchMoved")             \
    V(on_touch_ended_string, "onTouchEnded")             \
    V(on_touch_cancelled_string, "onTouchCancelled")     \
    V(on_focus_changed_string, "onFocusChanged")

#define PER_ISOLATE_CLASS_PROTOTYPE(V) \
    V(Vec2)                            \
    V(Vec3)                            \
    V(Vec4)                            \
    V(Rect)
