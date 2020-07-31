PROJECT(Tests C ASM)

set(KernelArchDir ${SynestiaOS_SOURCE_DIR}/SourceCode/Kernel/Arch/${SynestiaArch})
aux_source_directory(${Tests_SOURCE_DIR}/src TestsSrc)
aux_source_directory(${KernelArchDir} KernelArchSrc)
aux_source_directory(${KernelArchDir}/vmm/src KernelArchVMMSrc)

set(KernelArchForUnitTests KernelArchForUnitTests)
add_library(${KernelArchForUnitTests}
        OBJECT
        ${KernelArchSrc}
        ${KernelArchVMMSrc}
        ${KernelArchDir}/boot.S)
target_compile_definitions(${KernelArchForUnitTests} PRIVATE "-DENV_KERNEL_UNIT_TESTS")

target_include_vmm_header_files(${KernelArchForUnitTests})
target_include_kernel_header_files(${KernelArchForUnitTests})
target_include_libc_header_files(${KernelArchForUnitTests})

set(KernelUnitTestsImg KernelUnitTests.img)
add_executable(${KernelUnitTestsImg}
        ${TestsSrc}
        $<TARGET_OBJECTS:${KernelArchForUnitTests}>
        $<TARGET_OBJECTS:Kernel>
        $<TARGET_OBJECTS:LibC>
        $<TARGET_OBJECTS:LibMath>
        $<TARGET_OBJECTS:LibGfx>
        $<TARGET_OBJECTS:LibGUI>
        $<TARGET_OBJECTS:Console>
        $<TARGET_OBJECTS:BoardRaspberryPi3>)
target_include_tests_header_files(${KernelUnitTestsImg})
target_include_libc_header_files(${KernelUnitTestsImg})
target_include_raspberry_pi3_header_files(${KernelUnitTestsImg})
target_include_kernel_header_files(${KernelUnitTestsImg})
target_include_vmm_header_files(${KernelUnitTestsImg})

target_link_options(${KernelUnitTestsImg} PRIVATE -T ${KernelArchDir}/kernel.ld)
target_link_libraries(${KernelUnitTestsImg} PRIVATE gcc)
