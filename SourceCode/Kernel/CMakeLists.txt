project(Kernel C ASM)


aux_source_directory(${Kernel_SOURCE_DIR}/src KernelSrc)
add_library(${PROJECT_NAME}
        OBJECT
        ${KernelSrc}
        ${Kernel_SOURCE_DIR}/src/exception.S)

target_include_arch_header_files(${PROJECT_NAME})
target_include_kernel_header_files(${PROJECT_NAME})
target_include_libc_header_files(${PROJECT_NAME})
target_include_libelf_header_files(${PROJECT_NAME})
target_include_raspberry_pi_header_files(${PROJECT_NAME})
target_include_libgfx_header_files(${PROJECT_NAME})
target_include_libgui_header_files(${PROJECT_NAME})
