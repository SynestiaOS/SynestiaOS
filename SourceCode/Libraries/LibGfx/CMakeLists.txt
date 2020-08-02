PROJECT(LibGfx C ASM)

aux_source_directory(${LibGfx_SOURCE_DIR}/src LibGfxSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${LibGfxSrc})
target_include_libc_header_files(${PROJECT_NAME})
target_include_kernel_header_files(${PROJECT_NAME})
target_include_libgfx_header_files(${PROJECT_NAME})
target_include_raspberry_pi_header_files(${PROJECT_NAME})
target_include_libmath_header_files(${PROJECT_NAME})
