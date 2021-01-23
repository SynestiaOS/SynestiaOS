function(read_board_from_board_file OUT_board)
    if (NOT EXISTS ${SynestiaOS_SOURCE_DIR}/.board)
        message(FATAL_ERROR "file .board not found in directory ${SynestiaOS_SOURCE_DIR}")
    endif ()

    file(STRINGS ${SynestiaOS_SOURCE_DIR}/.board lines)
    foreach (line IN LISTS lines)
        # "#" started line is comment line, remove it
        string(REGEX REPLACE "\#.*" "" stripped_value "${line}")
        if (stripped_value)
            set(${OUT_board} "${stripped_value}" PARENT_SCOPE)
            break()
        endif ()
    endforeach ()
endfunction()

function(list_subdirs OUT_result IN_current_dir)
    FILE(GLOB children RELATIVE ${IN_current_dir} ${IN_current_dir}/*)
    message("children: ${children}")
    SET(temp_dirlist "")
    foreach (child ${children})
        if (IS_DIRECTORY ${IN_current_dir}/${child})
            LIST(APPEND temp_dirlist ${child})
        endif ()
    endforeach ()
    set(${OUT_result} ${temp_dirlist} PARENT_SCOPE)
endfunction()

# 1. check variable BOARD is defined via cmake command line as parameter, use it if it's defined
# 2. read file content from .board as BOARD variable
function(setup_board OUT_board)
    list_subdirs(supported_boards ${SYNESTIAOS_SOURCE_CODE_DIR}/Board)
    foreach (supported_board ${supported_boards})
        message(STATUS "detected supported board list: ${supported_board}")
    endforeach ()

    # read BOARD from cmake command line parameter
    if (DEFINED ${OUT_board})
        message(STATUS "DEFINED BOARD: ${OUT_board}")
    else ()
        read_board_from_board_file(${OUT_board})
        message(STATUS "READ BOARD FROM FILE: ${${OUT_board}}")
    endif ()

    list(FIND supported_boards ${${OUT_board}} index)
    if (NOT index EQUAL -1)
        message(STATUS "finally, found board \"${${OUT_board}}\"")
    else ()
        message(FATAL_ERROR "not supported board: ${${OUT_board}}. this is all the supported boards: ${supported_boards}")
    endif ()

    set(${OUT_board} ${${OUT_board}} PARENT_SCOPE)
endfunction()
