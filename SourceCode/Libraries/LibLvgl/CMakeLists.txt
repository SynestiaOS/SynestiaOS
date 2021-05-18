PROJECT(Liblvgl C ASM)

aux_source_directory(${Liblvgl_SOURCE_DIR}/src LibLvglSrc)
aux_source_directory(${Liblvgl_SOURCE_DIR}/port LibLvglSrc)


add_library(${PROJECT_NAME}
        OBJECT
        ${LibGUISrc})
target_include_libc_header_files(${PROJECT_NAME})
target_include_kernel_header_files(${PROJECT_NAME})
target_include_libgfx_header_files(${PROJECT_NAME})
target_include_libgui_header_files(${PROJECT_NAME})
target_include_raspberry_pi_header_files(${PROJECT_NAME})
target_include_libmath_header_files(${PROJECT_NAME})
