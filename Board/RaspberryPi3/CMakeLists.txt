project(BoardRaspberryPi3 C ASM)

aux_source_directory(${BoardRaspberryPi3_SOURCE_DIR}/src BoardRaspberryPi3Src)

add_library(${PROJECT_NAME}
        OBJECT
        ${BoardRaspberryPi3Src})
target_include_libc_header_files(${PROJECT_NAME})
target_include_raspberry_pi3_header_files(${PROJECT_NAME})
