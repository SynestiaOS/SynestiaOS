PROJECT(Tests C ASM)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/TempDir)
file(COPY ${SynestiaOS_SOURCE_DIR}/SourceCode/Kernel/Arch DESTINATION ${CMAKE_BINARY_DIR}/TempDir)
set(BootSourceCodeOnlyForTests ${CMAKE_BINARY_DIR}/TempDir/Arch/${SynestiaArch}/boot.s)
file(READ ${BootSourceCodeOnlyForTests} BootSourceCode)
# replace kernel_main to kernel_main_tests
string(REPLACE kernel_main
        kernel_main_tests KernelMainTests
        ${BootSourceCode})
file(WRITE ${BootSourceCodeOnlyForTests} ${KernelMainTests})

aux_source_directory(${CMAKE_BINARY_DIR}/TempDir/Arch/${SynestiaArch} KernelArchOnlyForTestsSrc)
aux_source_directory(${CMAKE_BINARY_DIR}/TempDir/Arch/${SynestiaArch}/vmm/src KernelArchOnlyForTestsVMMSrc)

add_library(KernelArchOnlyForTests
        OBJECT
        ${KernelArchOnlyForTestsSrc}
        ${KernelArchOnlyForTestsVMMSrc}
        ${CMAKE_BINARY_DIR}/TempDir/Arch/${SynestiaArch}/boot.s)

target_include_vmm_header_files(KernelArchOnlyForTests)
target_include_kernel_header_files(KernelArchOnlyForTests)
target_include_libc_header_files(KernelArchOnlyForTests)

aux_source_directory(${Tests_SOURCE_DIR}/src TestsSrc)
add_executable(${PROJECT_NAME}
        ${TestsSrc}
        $<TARGET_OBJECTS:KernelArchOnlyForTests>
        $<TARGET_OBJECTS:Kernel>
        $<TARGET_OBJECTS:BoardRaspberryPi3>
        $<TARGET_OBJECTS:Gfx>
        $<TARGET_OBJECTS:GUI>
        $<TARGET_OBJECTS:C>)

target_include_tests_header_files(${PROJECT_NAME})
target_include_libc_header_files(${PROJECT_NAME})
target_include_raspberry_pi3_header_files(${PROJECT_NAME})
target_include_kernel_header_files(${PROJECT_NAME})
target_include_vmm_header_files(${PROJECT_NAME})

target_link_options(${PROJECT_NAME} PRIVATE -T ${SynestiaOS_SOURCE_DIR}/SourceCode/Kernel/Arch/${SynestiaArch}/kernel.ld)

target_link_libraries(${PROJECT_NAME} PRIVATE gcc)
