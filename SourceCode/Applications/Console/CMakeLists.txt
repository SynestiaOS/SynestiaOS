PROJECT(Console CXX ASM)

aux_source_directory(${Console_SOURCE_DIR}/src ConsoleSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${ConsoleSrc})
target_include_application_console_header_files(${PROJECT_NAME})
target_include_libc_header_files(${PROJECT_NAME})

set(ConsoleElf Shell.elf)
add_executable(${ConsoleElf}
        ${ConsoleSrc})
