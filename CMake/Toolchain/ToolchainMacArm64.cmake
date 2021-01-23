message(STATUS "using aarch64-unknown-linux-gnu-gcc, version 8.3.0")

set(CMAKE_SYSTEM_NAME Darwin)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(arm_gcc_toolchain_file_name aarch64-unknown-linux-gnu.tar.xz)
set(arm_gcc_toolchain_path $ENV{HOME}/${arm_gcc_toolchain_file_name})
set(arm_gcc_toolchain_dir $ENV{HOME}/aarch64-unknown-linux-gnu)
set(arm_gcc_toolchain_url https://github.com/thinkski/osx-arm-linux-toolchains/releases/download/8.3.0/aarch64-unknown-linux-gnu.tar.xz)

if (NOT EXISTS ${arm_gcc_toolchain_dir})
    if (NOT EXISTS ${arm_gcc_toolchain_path})
        message(STATUS "downloading ${arm_gcc_toolchain_url}, wait a moment")
        file(DOWNLOAD ${arm_gcc_toolchain_url} ${arm_gcc_toolchain_path}
                EXPECTED_MD5 a8acb994a78185191e6be31f3573cec0
                TLS_VERIFY ON
                SHOW_PROGRESS)
    endif ()

    file(MAKE_DIRECTORY ${arm_gcc_toolchain_dir})
    message(STATUS "extracting ${arm_gcc_toolchain_path}, wait a moment")
    execute_process(COMMAND
            ${CMAKE_COMMAND} -E tar xvzf ${arm_gcc_toolchain_path}
            WORKING_DIRECTORY $ENV{HOME})
endif ()


set(CMAKE_FIND_ROOT_PATH ${arm_gcc_toolchain_dir}/bin)

set(CMAKE_C_COMPILER ${CMAKE_FIND_ROOT_PATH}/aarch64-unknown-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER ${CMAKE_FIND_ROOT_PATH}/aarch64-unknown-linux-gnu-g++)

set(CMAKE_CROSSCOMPILING_EMULATOR qemu-system-aarch64)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(TOOLCHAIN_PREFIX aarch64-unknown-linux-gnu-)
set(CMAKE_OBJCOPY ${arm_gcc_toolchain_dir}/bin/${TOOLCHAIN_PREFIX}objcopy)
