project(Kernel C ASM)


aux_source_directory(${Kernel_SOURCE_DIR}/src KernelSrc)
add_library(${PROJECT_NAME}
        OBJECT
        ${KernelSrc}
        ${Kernel_SOURCE_DIR}/src/exception.S)

target_include_kernel_header_files(${PROJECT_NAME})
target_include_libc_header_files(${PROJECT_NAME})

if (SynestiaPlatform STREQUAL pi2)
    target_include_raspberry_pi3_header_files(${PROJECT_NAME})
elseif (SynestiaPlatform STREQUAL pi3)
    target_include_raspberry_pi3_header_files(${PROJECT_NAME})
elseif (SynestiaPlatform STREQUAL pi4)
    target_include_raspberry_pi4_header_files(${PROJECT_NAME})
else ()
	message(FATAL_ERROR "unexpected SynestiaPlatform ${SynestiaPlatform}")
endif ()

target_include_vmm_header_files(${PROJECT_NAME})
target_include_libgfx_header_files(${PROJECT_NAME})
target_include_libgui_header_files(${PROJECT_NAME})
target_include_application_console_header_files(${PROJECT_NAME})

add_subdirectory(${Kernel_SOURCE_DIR}/Arch)
