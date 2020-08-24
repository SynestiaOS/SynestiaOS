PROJECT(KernelUnitTests C ASM)

set(KernelArchDir ${SynestiaOS_SOURCE_DIR}/SourceCode/Kernel/Arch/${SynestiaArch})
aux_source_directory(${KernelUnitTests_SOURCE_DIR}/src KernelUnitTestsSrc)
aux_source_directory(${KernelArchDir} KernelArchSrc)
aux_source_directory(${KernelArchDir}/vmm/src KernelArchVMMSrc)

set(KernelArchUnitTests KernelArchUnitTests)
add_library(${KernelArchUnitTests}
        OBJECT
        ${KernelArchSrc}
        ${KernelArchVMMSrc}
        ${KernelArchDir}/boot.S)
target_compile_definitions(${KernelArchUnitTests} PRIVATE "-DENV_KERNEL_UNIT_TESTS")

target_include_vmm_header_files(${KernelArchUnitTests})
target_include_kernel_header_files(${KernelArchUnitTests})
target_include_libc_header_files(${KernelArchUnitTests})

if (SynestiaPlatform STREQUAL pi2)
	set(boardObj BoardRaspberryPi)
elseif (SynestiaPlatform STREQUAL pi3)
	set(boardObj BoardRaspberryPi)
elseif (SynestiaPlatform STREQUAL pi4)
	set(boardObj BoardRaspberryPi)
else ()
	message(ERROR "unexpected PLATFORM ${PLATFORM}")
endif ()

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
	$<TARGET_OBJECTS:${boardObj}>)

target_sources(${KernelUnitTestsImg}
        PRIVATE
        ${SYNESTIAOS_FS_DIR}/initrd.o)

target_include_tests_header_files(${KernelUnitTestsImg})
target_include_libc_header_files(${KernelUnitTestsImg})
target_include_raspberry_pi_header_files(${KernelUnitTestsImg})
target_include_kernel_header_files(${KernelUnitTestsImg})
target_include_vmm_header_files(${KernelUnitTestsImg})

target_link_options(${KernelUnitTestsImg} PRIVATE -T ${KernelArchDir}/kernel.ld)
target_link_libraries(${KernelUnitTestsImg} PRIVATE gcc)
