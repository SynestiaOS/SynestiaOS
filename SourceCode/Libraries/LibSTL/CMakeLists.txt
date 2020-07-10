PROJECT(STL C ASM)

aux_source_directory(${STL_SOURCE_DIR}/src LibSTLSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${LibSTLSrc})
target_include_libc_header_files(${PROJECT_NAME})
target_include_libstl_header_files(${PROJECT_NAME})
target_include_raspberry_pi3_header_files(${PROJECT_NAME})
