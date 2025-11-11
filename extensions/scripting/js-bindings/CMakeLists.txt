include(${_AX_ROOT}/cmake/Modules/EmbedTextFiles.cmake)

set(ax_root ${_AX_ROOT})

set(js_bindings_manual_headers
    manual/js_bootstrap_bindings.h
	manual/js_isolate_data.h
	manual/js_isolate_properties.h
    manual/js_module_register.h
    manual/js_registry.h
    manual/js_storage.h
    manual/js_timers.h
    manual/JSConversions.h
    manual/JSEngine.h
    v8pp/config.hpp
	v8pp/call_from_v8.hpp
	v8pp/call_v8.hpp
    v8pp/class_detail.hpp
	v8pp/class.hpp
	v8pp/convert.hpp
	v8pp/function.hpp
	v8pp/module.hpp
	v8pp/object.hpp
	v8pp/property.hpp
	v8pp/ptr_traits.hpp
	v8pp/throw_ex.hpp
	v8pp/type_info.hpp
	v8pp/utility.hpp
)

set(js_bindings_manual_files
    manual/js_bootstrap_bindings.cpp
	manual/js_isolate_data.cpp
    manual/js_module_register.cpp
    manual/js_ops_builtin_types.cpp
    manual/js_ops_builtin_v8.cpp
    manual/js_storage.cpp
    manual/js_timers.cpp
    manual/JSConversions.cpp
    manual/JSEngine.cpp
    v8pp/class.cpp
    v8pp/throw_ex.cpp
)

set(js_bindings_auto_headers
    bindings/axjs_audioengine_auto.hpp
    bindings/axjs_base_auto.hpp
    bindings/axjs_controller_auto.hpp
    bindings/axjs_csloader_auto.hpp
    bindings/axjs_extension_auto.hpp
    bindings/axjs_spine_auto.hpp
    bindings/axjs_studio_auto.hpp
    bindings/axjs_ui_auto.hpp
    bindings/axjs_video_auto.hpp
    bindings/axjs_webview_auto.hpp
)

set(js_bindings_auto_files
    bindings/axjs_audioengine_auto.cpp
    bindings/axjs_base_auto.cpp
    bindings/axjs_controller_auto.cpp
    bindings/axjs_csloader_auto.cpp
    bindings/axjs_extension_auto.cpp
    bindings/axjs_spine_auto.cpp
    bindings/axjs_studio_auto.cpp
    bindings/axjs_ui_auto.cpp
    bindings/axjs_video_auto.cpp
    bindings/axjs_webview_auto.cpp
)

set(js_bindings_files
    ${js_bindings_manual_files}
    ${js_bindings_auto_files}
    ${_AX_DEPRECATED_SRC}
    )

set(js_bindings_headers
    ${js_bindings_manual_headers}
    ${js_bindings_auto_headers}
    ${_AX_DEPRECATED_HEADER}
    )

list(APPEND js_bindings_files ${js_bindings_headers})

set(_AX_JS_LIB axjs CACHE INTERNAL "The axmol js bindings lib name" )

add_library(${_AX_JS_LIB} STATIC ${js_bindings_files})

if(MSVC)
    target_compile_options(${_AX_JS_LIB} PRIVATE /bigobj)
endif()

get_target_property(js_ext_depend 3rdparty AX_JS_DEPEND)
target_link_libraries(${_AX_JS_LIB} ${js_ext_depend})

setup_ax_extension_config(${_AX_JS_LIB} DNTLINK)

target_include_directories(${_AX_JS_LIB}
    PUBLIC ${ax_root}/3rdparty/js/v8/include
    PUBLIC ${ax_root}/extensions/scripting
    PUBLIC ${ax_root}/extensions/scripting/js-bindings
    PRIVATE manual/platform/android
    PRIVATE manual/platform/android/jni
    PRIVATE ${ax_root}/extensions/spine/runtime/include
    PRIVATE ${ax_root}/extensions/spine/src
    PRIVATE ${ax_root}/extensions/cocostudio/src
    PRIVATE ${ax_root}/extensions/fairygui/src
    PRIVATE ${ax_root}/extensions/fairygui/src/fairygui
    PRIVATE ${ax_root}/extensions/Particle3D/src
)

add_text_files(${_AX_JS_LIB}
    HEADER "js_bootstrap_core.h"
    FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/manual/js/00_primordials.js"
        "${CMAKE_CURRENT_SOURCE_DIR}/manual/js/00_infra.js"
        "${CMAKE_CURRENT_SOURCE_DIR}/manual/js/01_core.js"
        "${CMAKE_CURRENT_SOURCE_DIR}/manual/js/02_console.js"
        "${CMAKE_CURRENT_SOURCE_DIR}/manual/js/02_axmol_ops.js"
        "${CMAKE_CURRENT_SOURCE_DIR}/manual/js/02_path.js"
        "${CMAKE_CURRENT_SOURCE_DIR}/manual/js/02_timers.js"
        "${CMAKE_CURRENT_SOURCE_DIR}/manual/js/03_require.js"
)

if(BUILD_SHARED_LIBS)
    target_compile_definitions(${_AX_JS_LIB} PRIVATE CCS_DLLIMPORT)
endif()

if(WINDOWS)
    if (WINRT)
        target_compile_options(${_AX_JS_LIB} PUBLIC /wd4700 /wd4201)
    endif()
endif()

set_target_properties(${_AX_JS_LIB}
                      PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      FOLDER "Extensions"
                      )

if(XCODE OR VS)
    ax_mark_code_files("${_AX_JS_LIB}")
endif()

