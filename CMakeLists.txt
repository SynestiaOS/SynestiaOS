cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# skip cmake compiler check
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(SynestiaOS LANGUAGES C ASM)

if(${SynestiaOS_SOURCE_DIR} STREQUAL ${SynestiaOS_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # compile commands can be used to help clang-tidy code analysis


include(${SynestiaOS_SOURCE_DIR}/CMake/ArchDetector.cmake)
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

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpic -ffreestanding -std=gnu11 -Wall -Wextra -g -nostdlib -D${PLATFORM}")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}")
message("CMAKE_C_FLAGS is ${CMAKE_C_FLAGS}")
message("CMAKE_ASM_FLAGS is ${CMAKE_ASM_FLAGS}")

add_subdirectory(${SynestiaOS_SOURCE_DIR}/Board/RaspberryPi3)
add_subdirectory(${SynestiaOS_SOURCE_DIR}/Kernel)
add_subdirectory(${SynestiaOS_SOURCE_DIR}/Libraries/LibC)

dump_cmake_variables()

