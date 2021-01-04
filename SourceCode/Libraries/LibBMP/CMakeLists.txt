PROJECT(LibBMP C ASM)

aux_source_directory(${LibBMP_SOURCE_DIR}/src LibBMPSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${LibBMPSrc})
target_include_libbmp_header_files(${PROJECT_NAME})
