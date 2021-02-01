project(KernelArch C ASM)

find_asm_source_files(ASM_SOURCE_FILES ${KernelArch_SOURCE_DIR}/src)
aux_source_directory(${KernelArch_SOURCE_DIR}/src KernelArchSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${KernelArchSrc}
        ${ASM_SOURCE_FILES})

target_include_arch_header_files(${PROJECT_NAME})
target_include_kernel_header_files(${PROJECT_NAME})
target_include_libc_header_files(${PROJECT_NAME})

if (SynestiaPlatform STREQUAL pi2)
    set(boardObj BoardRaspberryPi)
elseif (SynestiaPlatform STREQUAL pi3)
    set(boardObj BoardRaspberryPi)
elseif (SynestiaPlatform STREQUAL pi4)
    set(boardObj BoardRaspberryPi)
else ()
    message(ERROR "unexpected PLATFORM ${PLATFORM}")
endif ()

add_executable(${KernelName}
        $<TARGET_OBJECTS:KernelArch>
        $<TARGET_OBJECTS:Kernel>
        $<TARGET_OBJECTS:LibC>
        $<TARGET_OBJECTS:LibElf>
        $<TARGET_OBJECTS:LibMath>
        $<TARGET_OBJECTS:LibGfx>
        $<TARGET_OBJECTS:LibGUI>
        $<TARGET_OBJECTS:${boardObj}>)

target_link_options(${KernelName} PRIVATE -T ${KernelArch_SOURCE_DIR}/src/kernel.ld)

target_link_libraries(${KernelName} PRIVATE gcc)

#add_custom_target(OUTPUT initrd.o
#        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
#        COMMAND dd if=/dev/zero of=initrd.img bs=1KB count=32768
#        COMMAND mke2fs -m0 -F -v initrd.img
#        COMMAND mount initrd.img FS/tmp
#        COMMAND cp -r FS/initrd/* FS/tmp/
#        COMMAND unmount FS/tmp
#        COMMAND arm-none-eabi-objcopy -I binary -O elf32-littlearm -B arm initrd.img initrd.o
#        COMMENT "generate ramfs initrd.o")

target_sources(${KernelName}
        PRIVATE
        ${SYNESTIAOS_FS_DIR}/initrd.o)

add_custom_command(OUTPUT kernel.img
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_OBJCOPY} -O binary ${KernelName} kernel.img
        DEPENDS ${KernelName}
        COMMENT "objcopying ${KernelName} to kernel.img")

add_custom_target(kernelImage ALL
        DEPENDS kernel.img)

