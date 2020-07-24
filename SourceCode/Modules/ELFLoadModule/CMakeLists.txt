PROJECT(ModuleELF C ASM)

aux_source_directory(${ModuleELF_SOURCE_DIR}/src ModuleELFSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${ModuleELFSrc})
target_include_kernel_header_files(${PROJECT_NAME})
target_include_module_elfload_header_files(${PROJECT_NAME})
