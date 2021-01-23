cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

message(STATUS "cmake version: ${CMAKE_VERSION}")

# skip cmake compiler check
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)

project(SynestiaOS LANGUAGES C ASM)

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "cmake command line variable CMAKE_TOOLCHAIN_FILE should be defined to specify the compiler toolchain\n"
            "cmake command line should be: cmake -DCMAKE_TOOLCHAIN_FILE=${SynestiaOS_SOURCE_DIR}/CMake/Toolchain/ToolchainClang.cmake")
    message(FATAL_ERROR "")
endif ()

if (${SynestiaOS_SOURCE_DIR} STREQUAL ${SynestiaOS_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif ()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # compile commands can be used to help clang-tidy code analysis

set(SYNESTIAOS_SOURCE_CODE_DIR ${SynestiaOS_SOURCE_DIR}/SourceCode)
set(SYNESTIAOS_FS_DIR ${SynestiaOS_SOURCE_DIR}/FS)

set(KernelName Kernel.elf)

include(${SynestiaOS_SOURCE_DIR}/CMake/Setup.cmake)

# make config.h to be available globally
include_directories(${SYNESTIAOS_SOURCE_CODE_DIR}/Config/include)
add_subdirectory(${SYNESTIAOS_SOURCE_CODE_DIR})

set_directory_properties(PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.img)
