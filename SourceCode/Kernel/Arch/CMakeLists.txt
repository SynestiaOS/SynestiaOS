project(KernelArch C ASM)

aux_source_directory(${KernelArch_SOURCE_DIR}/${SynestiaArch} KernelArchSrc)
aux_source_directory(${KernelArch_SOURCE_DIR}/${SynestiaArch}/vmm/src KernelArchVMMSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${KernelArchSrc}
        ${KernelArchVMMSrc}
        ${KernelArch_SOURCE_DIR}/${SynestiaArch}/boot.S)

target_include_vmm_header_files(${PROJECT_NAME})
target_include_kernel_header_files(${PROJECT_NAME})
target_include_libc_header_files(${PROJECT_NAME})

add_executable(${KernelName}
        $<TARGET_OBJECTS:KernelArch>
        $<TARGET_OBJECTS:Kernel>
        $<TARGET_OBJECTS:LibC>
        $<TARGET_OBJECTS:LibMath>
        $<TARGET_OBJECTS:LibGfx>
        $<TARGET_OBJECTS:LibGUI>
        $<TARGET_OBJECTS:Console>
        $<TARGET_OBJECTS:BoardRaspberryPi3>)

target_link_options(${KernelName} PRIVATE -T ${KernelArch_SOURCE_DIR}/${SynestiaArch}/kernel.ld)

target_link_libraries(${KernelName} PRIVATE gcc)

#add_custom_command(TARGET ${KernelName} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E echo making Kernel7.img, wait a moment
#        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
#        COMMAND ${CMAKE_OBJCOPY} ${KernelName} -O binary Kernel7.img)
# TODO: ${CMAKE_OBJCOPY} not working here within docker env, find a better way to objcopy the kernel images
#add_custom_target(Objcopy ALL
#        COMMAND ${CMAKE_COMMAND} -E echo making Kernel7.img, wait a moment
#        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
#        COMMAND ${CMAKE_OBJCOPY} ${KernelName} -O binary Kernel7.img)
#