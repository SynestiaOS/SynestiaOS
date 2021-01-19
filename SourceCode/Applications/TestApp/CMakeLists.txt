PROJECT(TestApp C ASM)

aux_source_directory(${TestApp_SOURCE_DIR}/src TestAppSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${TestAppSrc})


target_include_application_testapp_header_files(${PROJECT_NAME})
target_include_libc_header_files(${PROJECT_NAME})

set(TestAppElf TestApp.elf)

target_link_options(${PROJECT_NAME} PRIVATE -T ${TestApp_SOURCE_DIR}/SynestiaELF.ld)

add_executable(${TestAppElf}
        ${TestAppSrc})


