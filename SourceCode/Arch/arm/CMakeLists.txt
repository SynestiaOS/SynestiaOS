project(KernelArch CXX ASM)

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

target_sources(${KernelName}
        PRIVATE
        ${SYNESTIAOS_FS_DIR}/initrd.o)

target_link_options(${KernelName} PRIVATE -T ${KernelArch_SOURCE_DIR}/src/kernel.ld)

target_link_libraries(${KernelName} PRIVATE gcc)

add_custom_command(TARGET ${KernelName} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo making Kernel7.img, wait a moment
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
