PROJECT(LibElf C ASM)

aux_source_directory(${LibElf_SOURCE_DIR}/src LibElfSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${LibElfSrc})
target_include_kernel_header_files(${PROJECT_NAME})
target_include_libelf_header_files(${PROJECT_NAME})
