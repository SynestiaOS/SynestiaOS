message(STATUS "detected c compiler id: ${CMAKE_C_COMPILER_ID}, version: ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "detected c++ compiler id: ${CMAKE_CXX_COMPILER_ID}, version: ${CMAKE_CXX_COMPILER_VERSION}")

# todo: add support for clang
#if (CMAKE_C_COMPILER_ID AND NOT CMAKE_C_COMPILER_ID STREQUAL "Clang")
#    message(FATAL_ERROR "[compiler] only clang is supported")
#endif ()
#
#if (CMAKE_CXX_COMPILER_ID AND NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#    message(FATAL_ERROR "[compiler] only clang++ is supported")
#endif ()
#
#set(CLANG_MIN_VERSION_REQUIRED 10.0.0)
#if (CMAKE_C_COMPILER_ID AND CMAKE_C_COMPILER_VERSION VERSION_LESS ${CLANG_MIN_VERSION_REQUIRED} AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS ${CLANG_MIN_VERSION_REQUIRED})
#    message(FATAL_ERROR "Clang version must be greater than ${CLANG_MIN_VERSION_REQUIRED}")
#endif ()

function(read_arch_compiler_flags_from_file IN_file OUT_flag)
    file(STRINGS ${IN_file} lines)

    foreach (line IN LISTS lines)
        # "#" started line is comment line, remove it
        string(REGEX REPLACE "\#.*" "" stripped "${line}")
        if (stripped)
            list(APPEND flag "${stripped}")
        endif ()
    endforeach ()
    message(STATUS ".flag: ${flag}")
    set(${OUT_flag} ${flag} PARENT_SCOPE)
endfunction()


if (NOT DEFINED OPTIMIZATION_LEVEL)
    if (CMAKE_BUILD_TYPE MATCHES "Rel")
        set(OPTIMIZATION_LEVEL 2)
    elseif (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(OPTIMIZATION_LEVEL 0)
    else ()
        set(OPTIMIZATION_LEVEL 0)
    endif ()
endif ()
message(STATUS "OPTIMIZATION_LEVEL: ${OPTIMIZATION_LEVEL}")

macro(disable_compiler_link_flags)
    set(CMAKE_C_LINK_FLAGS "")
    set(CMAKE_CXX_LINK_FLAGS "")
endmacro()

function(setup_compiler_flags IN_board IN_arch)
    set(arch_flag_file ${SYNESTIAOS_SOURCE_CODE_DIR}/Arch/${ARCH}/.flags)
    if (NOT EXISTS ${arch_flag_file})
        message(FATAL_ERROR "${arch_flag_file} must exist")
    endif ()

    message(STATUS "[arch] .flag file: ${arch_flag_file}")
    read_arch_compiler_flags_from_file(${arch_flag_file} arch_compiler_flags)
    message(STATUS "[arch] arch_compiler_flags is: ${arch_compiler_flags}")

    set(board_flag_file ${SYNESTIAOS_SOURCE_CODE_DIR}/Board/${IN_board}/.flags)
    if (EXISTS ${board_flag_file})
        message(STATUS "[board] .flag file: ${board_flag_file}")
        read_arch_compiler_flags_from_file(${board_flag_file} board_compiler_flags)
        message(STATUS "[board] board_compiler_flags is: ${board_compiler_flags}")
    endif ()

    set(board_macro ${IN_board})
    set(arch_macro ${IN_arch})

    set(ignore_specific_warnings
            "-Wno-unused-variable"
            "-Wno-unused-parameter"
            "-Wno-unused-function"
            "-Wno-unused-command-line-argument"
            )

    string(JOIN " " common_cmake_c_flags
            ${arch_compiler_flags}
            ${board_compiler_flags}

            "-D${board_macro}=1"
            "-DARCH_${arch_macro}=1"

            # "-v"
            "-O${OPTIMIZATION_LEVEL}"
            "-g"
            "-save-temps"
#            "-Wall"
#            "-Wextra"
#            "-Werror"
            ${ignore_specific_warnings}
            "-MD"
            # todo: clang required flag
#            "-fuse-ld=lld"
            "-fpic"
            "-ffreestanding"
            "-fno-builtin"
            "-fno-exceptions"
            "-nostdinc"
            "-nostdlib"
            "-nostartfiles"
            "-Wl,--no-dynamic-linker"
            "-Wl,--nostdlib"
            "-Wl,-error-limit=0"
            "-Wl,-v"
            )

    set(CMAKE_C_FLAGS "-std=c11 ${common_cmake_c_flags}" PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS "-std=c++20 ${common_cmake_c_flags}" PARENT_SCOPE)
    set(CMAKE_ASM_FLAGS "-std=c11 ${common_cmake_c_flags}" PARENT_SCOPE)
endfunction()

macro(print_compiler_flags)
    string(REPEAT "=" 300 compiler_flags_separator)
    message(STATUS "${compiler_flags_separator}")
    message(STATUS "${compiler_flags_separator}")
    message(STATUS "CMAKE_ASM_FLAGS:  ${CMAKE_ASM_FLAGS}")
    message(STATUS "CMAKE_C_FLAGS:    ${CMAKE_C_FLAGS}")
    message(STATUS "CMAKE_CXX_FLAGS:  ${CMAKE_CXX_FLAGS}")
    message(STATUS "CMAKE_OBJCOPY:    ${CMAKE_OBJCOPY}")
    message(STATUS "${compiler_flags_separator}")
    message(STATUS "${compiler_flags_separator}")
endmacro()
