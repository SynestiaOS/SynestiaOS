cmake_minimum_required(VERSION 3.12)

# tricky way to skip cmake compiler check
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(SynestiaOS C ASM)

set(CMAKE_C_STANDARD 11)

include(${SynestiaOS_SOURCE_DIR}/CMake/ArchDetector.cmake)
#include(${SynestiaOS_SOURCE_DIR}/CMake/SetupCompiler.cmake)
include(${SynestiaOS_SOURCE_DIR}/CMake/VarsDump.cmake)


if (SynestiaArch STREQUAL arm)
    set(TOOLCHAIN_PREFIX arm-none-eabi-)
    set(PLATFORM RASPI2)
    set(CMAKE_C_FLAGS "-O2 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7")
elseif (SynestiaArch STREQUAL arm64)
    set(TOOLCHAIN_PREFIX aarch64-linux-gnu-)
    set(PLATFORM RASPI3)
    set(CMAKE_C_FLAGS "-O2 -mfpu=crypto-neon-fp-armv8 -mfloat-abi=hard -march=armv8-a+crc -mcpu=cortex-a53")
else ()
    message(FATAL_ERROR "unexpected ARCH ${SynestiaArch}")
endif ()
message("TOOLCHAIN_PREFIX is ${TOOLCHAIN_PREFIX}")
message("PLATFORM is ${PLATFORM}")
#string(APPEND CMAKE_C_FLAGS " -fpic -ffreestanding -std=gnu11 -Wall -Wextra -g -nostdlib -fno-builtin -D${PLATFORM}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpic -ffreestanding -std=gnu11 -Wall -Wextra -g -nostdlib -fno-builtin -D${PLATFORM}")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}")
message("CMAKE_C_FLAGS is ${CMAKE_C_FLAGS}")

add_subdirectory(${SynestiaOS_SOURCE_DIR}/Board/RaspberryPi3)
add_subdirectory(${SynestiaOS_SOURCE_DIR}/Kernel)
add_subdirectory(${SynestiaOS_SOURCE_DIR}/Libraries/LibC)

#dump_cmake_variables()
