project(KernelArch C ASM)

aux_source_directory(${KernelArch_SOURCE_DIR}/${SynestiaArch} KernelArchSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${KernelArchSrc}
        ${KernelArch_SOURCE_DIR}/${SynestiaArch}/boot.S)

add_executable(${KernelName}
        $<TARGET_OBJECTS:KernelArch>
        )

target_link_options(${KernelName} PRIVATE -T ${KernelArch_SOURCE_DIR}/${SynestiaArch}/kernel.ld)

target_link_libraries(${KernelName} PRIVATE gcc)

add_custom_command(TARGET ${KernelName} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo making Kernel7.img, wait a moment
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_OBJCOPY} ${KernelName} -O binary Kernel7.img)
