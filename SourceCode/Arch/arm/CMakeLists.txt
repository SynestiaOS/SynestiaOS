project(KernelArch C ASM)

find_asm_source_files(ASM_SOURCE_FILES ${KernelArch_SOURCE_DIR}/src)
aux_source_directory(${KernelArch_SOURCE_DIR}/src KernelArchSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${KernelArchSrc}
        ${ASM_SOURCE_FILES})

target_include_arch_header_files(${PROJECT_NAME})
target_include_kernel_header_files(${PROJECT_NAME})
target_include_libc_header_files(${PROJECT_NAME})


add_executable(${KernelName}
        $<TARGET_OBJECTS:KernelArch>
        $<TARGET_OBJECTS:Kernel>
        $<TARGET_OBJECTS:LibC>
        $<TARGET_OBJECTS:LibElf>
        $<TARGET_OBJECTS:LibMath>
        $<TARGET_OBJECTS:LibGfx>
        $<TARGET_OBJECTS:LibGUI>
        $<TARGET_OBJECTS:BoardRaspberryPi>)

target_sources(${KernelName}
        PRIVATE
        ${SYNESTIAOS_FS_DIR}/initrd.o)

target_link_options(${KernelName} PRIVATE -T ${KernelArch_SOURCE_DIR}/src/kernel.ld)

#target_link_libraries(${KernelName} PRIVATE gcc)

add_custom_command(OUTPUT kernel.img
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_OBJCOPY} -O binary ${KernelName} kernel.img
        DEPENDS ${KernelName}
        COMMENT "objcopying ${KernelName} to kernel.img")
add_custom_target(kernelImage ALL
        DEPENDS kernel.img)

