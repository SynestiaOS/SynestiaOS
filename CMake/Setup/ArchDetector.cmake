# read .arch file from board dir
function(read_arch_from_arch_file IN_board OUT_arch)
    if (NOT EXISTS ${SYNESTIAOS_SOURCE_CODE_DIR}/Board/${IN_board}/.arch)
        message(FATAL_ERROR "file .arch not found in directory ${SYNESTIAOS_SOURCE_CODE_DIR}/Board/${IN_board}")
    endif ()

    file(STRINGS ${SYNESTIAOS_SOURCE_CODE_DIR}/Board/${IN_board}/.arch lines)
    foreach (line IN LISTS lines)
        # "#" started line is comment line, remove it
        string(REGEX REPLACE "\#.*" "" stripped_value "${line}")
        if (stripped_value)
            set(${OUT_arch} "${stripped_value}" PARENT_SCOPE)
            break()
        endif ()
    endforeach ()
endfunction()

function(setup_arch IN_board OUT_arch)
    list_subdirs(supported_archs ${SYNESTIAOS_SOURCE_CODE_DIR}/Arch)

    foreach (SUPPORTED_ARCH ${supported_archs})
        message(STATUS "detected supported arch list: ${supported_archs}")
    endforeach ()

    read_arch_from_arch_file(${IN_board} arch)
    set(${OUT_arch} ${arch} PARENT_SCOPE)

    list(FIND supported_archs ${arch} index)
    if (NOT index EQUAL -1)
        message(STATUS "finally, found arch \"${arch}\"")
    else ()
        message(FATAL_ERROR "not supported arch: ${arch}. this is all the supported arch: ${supported_archs}")
    endif ()
endfunction()
