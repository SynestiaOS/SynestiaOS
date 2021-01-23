PROJECT(KernelUnitTests C ASM)

set(KernelArchDir ${SynestiaOS_SOURCE_DIR}/SourceCode/Arch/${ARCH})

find_asm_source_files(ASM_SOURCE_FILES ${KernelArchDir}/src)
aux_source_directory(${KernelUnitTests_SOURCE_DIR}/src KernelUnitTestsSrc)
aux_source_directory(${KernelArchDir}/src KernelArchSrc)

# todo: refactor, move the library definition to Arch dir
set(KernelArchUnitTests KernelArchUnitTests)
add_library(${KernelArchUnitTests}
        OBJECT
        ${KernelArchSrc}
        ${ASM_SOURCE_FILES})
target_compile_definitions(${KernelArchUnitTests} PRIVATE "-DENV_KERNEL_UNIT_TESTS")

target_include_arch_header_files(${KernelArchUnitTests})
target_include_kernel_header_files(${KernelArchUnitTests})
target_include_libc_header_files(${KernelArchUnitTests})
target_include_libmath_header_files(${KernelArchUnitTests})

set(KernelUnitTestsImg KernelUnitTests.elf)
add_executable(${KernelUnitTestsImg}
        ${KernelUnitTestsSrc}
        $<TARGET_OBJECTS:${KernelArchUnitTests}>
        $<TARGET_OBJECTS:Kernel>
        $<TARGET_OBJECTS:LibC>
        $<TARGET_OBJECTS:LibElf>
        $<TARGET_OBJECTS:LibMath>
        $<TARGET_OBJECTS:LibGfx>
        $<TARGET_OBJECTS:LibGUI>
        $<TARGET_OBJECTS:BoardRaspberryPi>)

target_sources(${KernelUnitTestsImg}
        PRIVATE
        ${SYNESTIAOS_FS_DIR}/initrd.o)

target_include_tests_header_files(${KernelUnitTestsImg})
target_include_libc_header_files(${KernelUnitTestsImg})
target_include_arch_header_files(${KernelUnitTestsImg})
target_include_raspberry_pi_header_files(${KernelUnitTestsImg})
target_include_kernel_header_files(${KernelUnitTestsImg})
target_include_libmath_header_files(${KernelUnitTestsImg})

target_link_options(${KernelUnitTestsImg} PRIVATE -T ${KernelArchDir}/src/kernel.ld)
target_link_libraries(${KernelUnitTestsImg} PRIVATE gcc)
