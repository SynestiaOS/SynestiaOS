PROJECT(LibGUI C ASM)

aux_source_directory(${LibGUI_SOURCE_DIR}/src LibGUISrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${LibGUISrc})
target_include_libc_header_files(${PROJECT_NAME})
target_include_kernel_header_files(${PROJECT_NAME})
target_include_libgfx_header_files(${PROJECT_NAME})
target_include_libgui_header_files(${PROJECT_NAME})
target_include_raspberry_pi_header_files(${PROJECT_NAME})
