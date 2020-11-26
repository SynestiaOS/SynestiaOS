project(KernelArch C ASM)

find_asm_source_files(ASM_SOURCE_FILES ${KernelArch_SOURCE_DIR}/src)
aux_source_directory(${KernelArch_SOURCE_DIR}/src KernelArchSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${KernelArchSrc}
        ${ASM_SOURCE_FILES})

add_executable(${KernelName}
        $<TARGET_OBJECTS:KernelArch>
        )

target_link_options(${KernelName} PRIVATE -T ${KernelArch_SOURCE_DIR}/src/kernel.ld)

target_link_libraries(${KernelName} PRIVATE gcc)

add_custom_command(TARGET ${KernelName} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo making Kernel7.img, wait a moment
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_OBJCOPY} ${KernelName} -O binary Kernel7.img)
