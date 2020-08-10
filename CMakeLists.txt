cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# skip cmake compiler check
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)

project(SynestiaOS LANGUAGES C ASM)

if(${SynestiaOS_SOURCE_DIR} STREQUAL ${SynestiaOS_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # compile commands can be used to help clang-tidy code analysis

set(SYNESTIAOS_SOURCE_CODE_DIR ${SynestiaOS_SOURCE_DIR}/SourceCode)
set(SYNESTIAOS_FS_DIR ${SynestiaOS_SOURCE_DIR}/FS)
set(KernelName Kernel.elf)

set(CMAKE_MODULE_PATH "${SynestiaOS_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

include(${SynestiaOS_SOURCE_DIR}/CMake/ArchDetector.cmake)
include(${SynestiaOS_SOURCE_DIR}/CMake/PlatformDetector.cmake)
include(${SynestiaOS_SOURCE_DIR}/CMake/VarsDump.cmake)
include(${SynestiaOS_SOURCE_DIR}/CMake/HeaderFiles.cmake)


message(STATUS "PLATFORM is ${PLATFORM}")

if (SynestiaArch STREQUAL arm)
    set(CMAKE_C_FLAGS "-O0 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7")
elseif (SynestiaArch STREQUAL aarch64)
    set(CMAKE_C_FLAGS "-O0 -mfpu=crypto-neon-fp-armv8 -mfloat-abi=hard -march=armv8-a+crc -mcpu=cortex-a53")
else ()
    message(FATAL_ERROR "unexpected ARCH ${SynestiaArch}")
endif ()
message(STATUS "ARCH is ${ARCH}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -MD -fpic -ffreestanding -std=gnu11 -Wall -Wextra -g -nostdlib -D${SynestiaPlatformMacro}")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}")

message(STATUS "CMAKE_C_FLAGS is ${CMAKE_C_FLAGS}")
message(STATUS "CMAKE_ASM_FLAGS is ${CMAKE_ASM_FLAGS}")
message(STATUS "TOOLCHAIN_PREFIX is ${TOOLCHAIN_PREFIX}")
message(STATUS "CMAKE_OBJCOPY is ${CMAKE_OBJCOPY}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(${SynestiaOS_SOURCE_DIR}/SourceCode)

dump_cmake_variables()

