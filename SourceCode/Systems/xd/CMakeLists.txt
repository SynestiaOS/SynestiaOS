PROJECT(X C ASM)

aux_source_directory(${X_SOURCE_DIR}/src XSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${XSrc})
target_include_system_x_header_files(${PROJECT_NAME})
target_include_libc_header_files(${PROJECT_NAME})

set(XElf X.elf)
add_executable(${XElf}
        ${XSrc})
