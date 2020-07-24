project(BoardRaspberryPi4 C ASM)

aux_source_directory(${BoardRaspberryPi4_SOURCE_DIR}/src BoardRaspberryPi4Src)

add_library(${PROJECT_NAME}
        OBJECT
        ${BoardRaspberryPi4Src})
target_include_libc_header_files(${PROJECT_NAME})
target_include_raspberry_pi4_header_files(${PROJECT_NAME})
target_include_kernel_header_files(${PROJECT_NAME})
