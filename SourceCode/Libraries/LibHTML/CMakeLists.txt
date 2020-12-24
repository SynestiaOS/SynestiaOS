PROJECT(LibHTML C ASM)

aux_source_directory(${LibHTML_SOURCE_DIR}/src LibHTMLSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${LibHTMLSrc})
target_include_libc_header_files(${PROJECT_NAME})
target_include_libstring_header_files(${PROJECT_NAME})
target_include_libhtml_header_files(${PROJECT_NAME})
