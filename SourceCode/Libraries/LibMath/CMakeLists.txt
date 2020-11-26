PROJECT(LibMath C ASM)

aux_source_directory(${LibMath_SOURCE_DIR}/src LibMathSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${LibMathSrc})
target_include_libc_header_files(${PROJECT_NAME})
target_include_libmath_header_files(${PROJECT_NAME})
