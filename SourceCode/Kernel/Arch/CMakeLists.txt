project(KernelArch C ASM)

aux_source_directory(${KernelArch_SOURCE_DIR}/${SynestiaArch} KernelArchSrc)
aux_source_directory(${KernelArch_SOURCE_DIR}/${SynestiaArch}/vmm/src KernelArchVMMSrc)

add_executable(${KernelName}
        ${KernelArchSrc}
        ${KernelArchVMMSrc}
        ${KernelArch_SOURCE_DIR}/${SynestiaArch}/boot.s
        $<TARGET_OBJECTS:Kernel>
        $<TARGET_OBJECTS:C>
        $<TARGET_OBJECTS:BoardRaspberryPi3>)


target_include_vmm_header_files(${KernelName})

target_link_options(${KernelName} PRIVATE -T ${KernelArch_SOURCE_DIR}/${SynestiaArch}/kernel.ld)

target_link_libraries(${KernelName} PRIVATE gcc)

add_custom_command(TARGET ${KernelName} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo making Kernel7.img, wait a moment
        COMMAND ${CMAKE_OBJCOPY} ${KernelName} -O binary Kernel7.img)
