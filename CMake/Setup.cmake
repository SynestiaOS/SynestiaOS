# find all cmake files, and then include the file
file(GLOB cmake_files LIST_DIRECTORIES false ${SynestiaOS_SOURCE_DIR}/CMake/Setup/*.cmake)
message(STATUS "found CmakeFiles: ${cmake_files}")
foreach (cmake_file ${cmake_files})
    message(STATUS "include ${cmake_file}")
    include(${cmake_file})
endforeach ()

message(STATUS "********** setup began **********")

setup_board(BOARD)
message(STATUS ">>> building board: ${BOARD}")

setup_arch(${BOARD} ARCH)
message(STATUS ">>> building arch: ${ARCH}")

disable_compiler_link_flags()
setup_compiler_flags(${BOARD} ${ARCH})
print_compiler_flags()

message(STATUS "********** setup ended **********")

dump_cmake_variables()
