PROJECT(LibC C ASM)

aux_source_directory(${LibC_SOURCE_DIR}/src LibCSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${LibCSrc})
target_include_libc_header_files(${PROJECT_NAME})
target_include_raspberry_pi3_header_files(${PROJECT_NAME})
