PROJECT(LibCSS C ASM)

aux_source_directory(${LibCSS_SOURCE_DIR}/src LibCSSSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${LibCSSSrc})
target_include_libcss_header_files(${PROJECT_NAME})
