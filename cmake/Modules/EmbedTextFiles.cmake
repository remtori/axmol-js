# Modern text file embedding with header/source generation
# Usage: add_text_files(target HEADER "filename.h" FILES file1 file2 ...)

function(add_text_files target)
    cmake_parse_arguments(
        EMBED_TEXT
        ""
        "HEADER"
        "FILES"
        ${ARGN}
    )

    if(NOT EMBED_TEXT_HEADER)
        message(FATAL_ERROR "add_text_files: HEADER is required")
    endif()

    if(NOT EMBED_TEXT_FILES)
        message(FATAL_ERROR "add_text_files: FILES is required")
    endif()

    # Create generated directory in build folder
    set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/codegen/generated")
    file(MAKE_DIRECTORY "${generated_dir}")

    # Define output files
    set(header_file "${generated_dir}/${EMBED_TEXT_HEADER}")
    set(source_file "${generated_dir}/${EMBED_TEXT_HEADER}.cpp")

    # Function to sanitize filename to valid C++ identifier
    function(sanitize_identifier input_name output_var)
        string(REGEX REPLACE "[^a-zA-Z0-9_]" "_" sanitized "${input_name}")
        set(${output_var} "_${sanitized}" PARENT_SCOPE)
    endfunction()

    # Generate header content
    set(header_content "#pragma once\n")
    string(APPEND header_content "#include <string_view>\n\n")
    string(APPEND header_content "namespace generated {\n\n")

    # Generate source content
    set(source_content "// Auto-generated file - do not edit manually\n")
    string(APPEND source_content "#include \"generated/${EMBED_TEXT_HEADER}\"\n\n")
    string(APPEND source_content "namespace generated {\n\n")

    # Process each file
    foreach(text_file ${EMBED_TEXT_FILES})
        if(NOT EXISTS "${text_file}")
            message(FATAL_ERROR "add_text_files: File not found: ${text_file}")
        endif()

        # Get filename without path and extension for variable name
        get_filename_component(file_name "${text_file}" NAME_WE)
        sanitize_identifier("${file_name}" var_name)

        # Read the file content
        file(READ "${text_file}" file_content)

        # Add declaration to header
        string(APPEND header_content "extern const std::string_view ${var_name};\n")

        # Add definition to source using raw string literal
        string(APPEND source_content "const std::string_view ${var_name} = R\"TEXTEMBEDDED(\n${file_content}\n)TEXTEMBEDDED\";\n\n")
    endforeach()

    # Close namespaces
    string(APPEND header_content "\n} // namespace generated\n")
    string(APPEND source_content "} // namespace generated\n")

    # Write the files
    file(WRITE "${header_file}" "${header_content}")
    file(WRITE "${source_file}" "${source_content}")

    # Add the source file to the target
    target_sources(${target} PRIVATE "${source_file}")

    # Add include directory so the target can #include "header.h"
    target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/codegen")

    # Add dependencies so CMake knows to regenerate when text files change
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${EMBED_TEXT_FILES})

    message(STATUS "Generated text embedding: ${header_file}")
endfunction()
