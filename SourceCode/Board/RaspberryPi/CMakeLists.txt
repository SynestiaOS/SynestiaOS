project(BoardRaspberryPi CXX ASM)

aux_source_directory(${BoardRaspberryPi_SOURCE_DIR}/src BoardRaspberryPiSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${BoardRaspberryPiSrc})
target_include_libc_header_files(${PROJECT_NAME})
target_include_raspberry_pi_header_files(${PROJECT_NAME})
target_include_kernel_header_files(${PROJECT_NAME})
