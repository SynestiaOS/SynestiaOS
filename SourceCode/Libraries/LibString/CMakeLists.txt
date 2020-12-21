PROJECT(LibString C ASM)

aux_source_directory(${LibString_SOURCE_DIR}/src LibStringSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${LibStringSrc})
target_include_libc_header_files(${PROJECT_NAME})
target_include_libstring_header_files(${PROJECT_NAME})
