
set(lib_name v8)
set(target_name ${lib_name})
project(${lib_name})

if(WINDOWS)
	add_library(${target_name} SHARED IMPORTED GLOBAL)
else()
	add_library(${target_name} STATIC IMPORTED GLOBAL)
endif()

set_target_properties(${target_name} PROPERTIES
	INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include"
	INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include"
)

if(WINDOWS)
	set_target_properties(${target_name} PROPERTIES
		IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/prebuilt/${PLATFORM_NAME}/${ARCH_ALIAS}/v8_monolith.lib"
		INTERFACE_COMPILE_DEFINITIONS V8_COMPRESS_POINTERS V8_COMPRESS_POINTERS_IN_SHARED_CAGE V8_31BIT_SMIS_ON_64BIT_ARCH
	)

	add_library(v8_libbase STATIC IMPORTED GLOBAL)
	set_target_properties(v8_libbase PROPERTIES
		IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/prebuilt/${PLATFORM_NAME}/${ARCH_ALIAS}/v8_libbase.lib"
	)

	add_library(v8_libplatform STATIC IMPORTED GLOBAL)
	set_target_properties(v8_libplatform PROPERTIES
		IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/prebuilt/${PLATFORM_NAME}/${ARCH_ALIAS}/v8_libplatform.lib"
	)

	target_link_libraries(${target_name} INTERFACE v8_libbase v8_libplatform)
elseif(ANDROID)
	set_target_properties(${target_name} PROPERTIES
		IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/prebuilt/${PLATFORM_NAME}/${ARCH_ALIAS}/libv8_monolith.a"
		INTERFACE_COMPILE_DEFINITIONS V8_COMPRESS_POINTERS V8_COMPRESS_POINTERS_IN_SHARED_CAGE V8_31BIT_SMIS_ON_64BIT_ARCH
	)
else()
	set_target_properties(${target_name} PROPERTIES
		IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/prebuilt/${PLATFORM_NAME}/libv8_monolith.a"
		INTERFACE_COMPILE_DEFINITIONS V8_COMPRESS_POINTERS V8_COMPRESS_POINTERS_IN_SHARED_CAGE V8_31BIT_SMIS_ON_64BIT_ARCH
	)
endif()
