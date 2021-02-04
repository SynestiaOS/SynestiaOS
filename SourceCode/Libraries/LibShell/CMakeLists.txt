PROJECT(LibShell C ASM)

aux_source_directory(${LibShell_SOURCE_DIR}/src LibShellSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${LibShellSrc})
target_include_libc_header_files(${PROJECT_NAME})
target_include_libshell_header_files(${PROJECT_NAME})
