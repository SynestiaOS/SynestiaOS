PROJECT(UnitTest C ASM)

aux_source_directory(${UnitTest_SOURCE_DIR} UnitTestSrc)
message("UnitTestSrc is ${UnitTestSrc}")

add_executable(${PROJECT_NAME}
        ${UnitTestSrc}
        $<TARGET_OBJECTS:KernelArch>
        $<TARGET_OBJECTS:Kernel>
        $<TARGET_OBJECTS:BoardRaspberryPi3>
        $<TARGET_OBJECTS:C>)
#target_compile_definitions(${PROJECT_NAME} PRIVATE -Dkernel_main=kernel_main_test)

target_include_libc_header_files(${PROJECT_NAME})
target_include_raspberry_pi3_header_files(${PROJECT_NAME})
target_include_kernel_header_files(${PROJECT_NAME})
target_include_vmm_header_files(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE ${UnitTest_SOURCE_DIR}/ThirdParty/Greatest)

target_link_options(${PROJECT_NAME} PRIVATE -T ${SynestiaOS_SOURCE_DIR}/SourceCode/Kernel/Arch/${SynestiaArch}/kernel.ld)

target_link_libraries(${PROJECT_NAME} PRIVATE gcc)
