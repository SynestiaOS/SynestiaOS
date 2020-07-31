set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

find_program(MacAarch64 aarch64-none-elf-gcc REQUIRED)
if (NOT MacAarch64)
    message(FATAL_ERROR "aarch64-none-elf-gcc not found!!!\n"
            "run `brew tap SergioBenitez/osxct && brew install aarch64-none-elf` to install the toolchain")
else ()
    message(STATUS "found aarch64-none-elf-gcc ${MacAarch64}")
endif ()

set(CMAKE_C_COMPILER aarch64-none-elf-gcc)
set(CMAKE_CXX_COMPILER aarch64-none-elf-g++)

set(CMAKE_CROSSCOMPILING_EMULATOR qemu-system-aarch64)

set(CMAKE_FIND_ROOT_PATH /usr/local/bin)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(TOOLCHAIN_PREFIX aarch64-none-elf-)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
