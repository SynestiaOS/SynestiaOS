PROJECT(TestApp C ASM)

aux_source_directory(${TestApp_SOURCE_DIR}/src TestAppSrc)

add_executable(${PROJECT_NAME}  $<TARGET_OBJECTS:LibC> ${TestAppSrc})

target_include_application_testapp_header_files(${PROJECT_NAME})
target_include_libc_header_files(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE gcc)
