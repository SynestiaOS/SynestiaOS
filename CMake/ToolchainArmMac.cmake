set(CMAKE_SYSTEM_NAME Darwin)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(arm_gcc_toolchain_file_name gcc-arm-none-eabi-9-2020-q2-update-mac.tar.bz2)
set(arm_gcc_toolchain_path $ENV{HOME}/${arm_gcc_toolchain_file_name})
set(arm_gcc_toolchain_dir $ENV{HOME}/gcc-arm-none-eabi-9-2020-q2-update)
set(arm_gcc_toolchain_url https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-mac.tar.bz2)

if (NOT EXISTS ${arm_gcc_toolchain_dir})
    if (NOT EXISTS ${arm_gcc_toolchain_path})
        message(STATUS "downloading ${arm_gcc_toolchain_url}, wait a moment")
        file(DOWNLOAD ${arm_gcc_toolchain_url} ${arm_gcc_toolchain_path}
                EXPECTED_MD5 75a171beac35453fd2f0f48b3cb239c3
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

set(CMAKE_C_COMPILER ${CMAKE_FIND_ROOT_PATH}/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${CMAKE_FIND_ROOT_PATH}/arm-none-eabi-g++)

set(CMAKE_CROSSCOMPILING_EMULATOR qemu-system-arm)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
