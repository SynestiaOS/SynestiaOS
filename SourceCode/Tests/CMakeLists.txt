PROJECT(Tests C ASM)

aux_source_directory(${C_SOURCE_DIR}/src TestsSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${TestsSrc})
target_include_libc_header_files(${PROJECT_NAME})
target_include_raspberry_pi3_header_files(${PROJECT_NAME})
