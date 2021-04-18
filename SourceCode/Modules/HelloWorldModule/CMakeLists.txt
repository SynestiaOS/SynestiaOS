PROJECT(HelloWorldModule C ASM)

aux_source_directory(${HelloWorldModule_SOURCE_DIR}/src HelloWorldModuleSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${HelloWorldModuleSrc})

target_include_kernel_header_files(${PROJECT_NAME})
target_include_libc_header_files(${PROJECT_NAME})