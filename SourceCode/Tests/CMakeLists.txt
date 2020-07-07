PROJECT(Tests C ASM)

aux_source_directory(${Tests_SOURCE_DIR}/src TestsSrc)

add_executable(${PROJECT_NAME}
        ${TestsSrc}
        $<TARGET_OBJECTS:KernelArch>
        $<TARGET_OBJECTS:Kernel>
        $<TARGET_OBJECTS:BoardRaspberryPi3>
        $<TARGET_OBJECTS:Gfx>
        $<TARGET_OBJECTS:GUI>
        $<TARGET_OBJECTS:C>)

#target_compile_definitions(${PROJECT_NAME} PRIVATE ENV_TESTS)

target_include_tests_header_files(${PROJECT_NAME})
target_include_libc_header_files(${PROJECT_NAME})
target_include_raspberry_pi3_header_files(${PROJECT_NAME})
target_include_kernel_header_files(${PROJECT_NAME})
target_include_vmm_header_files(${PROJECT_NAME})

target_link_options(${PROJECT_NAME} PRIVATE -T ${SynestiaOS_SOURCE_DIR}/SourceCode/Kernel/Arch/${SynestiaArch}/kernel.ld)

target_link_libraries(${PROJECT_NAME} PRIVATE gcc)
