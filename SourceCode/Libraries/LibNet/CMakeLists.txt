PROJECT(LibNet CXX ASM)

aux_source_directory(${LibNet_SOURCE_DIR}/src LibNetSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${LibNetSrc})
target_include_libnet_header_files(${PROJECT_NAME})
target_include_libc_header_files(${PROJECT_NAME})
