#pragma once

/// v8pp library version
#define V8PP_VERSION       "2.1.1"
#define V8PP_VERSION_MAJOR 2
#define V8PP_VERSION_MINOR 1
#define V8PP_VERSION_PATCH 1

/// v8::Isolate data slot number, used in v8pp for shared data
#if !defined(V8PP_ISOLATE_DATA_SLOT)
#    define V8PP_ISOLATE_DATA_SLOT 3
#endif

#if defined(_MSC_VER)
#    define V8PP_EXPORT __declspec(dllexport)
#    define V8PP_IMPORT __declspec(dllimport)
#elif __GNUC__ >= 4
#    define V8PP_EXPORT __attribute__((__visibility__("default")))
#    define V8PP_IMPORT V8PP_EXPORT
#else
#    define V8PP_EXPORT
#    define V8PP_IMPORT
#endif

#ifndef V8PP_HEADER_ONLY
#    define V8PP_HEADER_ONLY 0
#endif

#if V8PP_HEADER_ONLY
#    define V8PP_IMPL inline
#else
#    define V8PP_IMPL
#endif

#define V8PP_STRINGIZE(s)  V8PP_STRINGIZE0(s)
#define V8PP_STRINGIZE0(s) #s
