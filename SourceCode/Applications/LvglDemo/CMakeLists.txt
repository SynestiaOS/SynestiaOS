PROJECT(LvglDemo C ASM)

aux_source_directory(${LvglDemo_SOURCE_DIR}/src LvglDemoSrc)

add_executable(${PROJECT_NAME}  $<TARGET_OBJECTS:LibC> ${LvglDemoSrc})

target_include_application_testapp_header_files(${PROJECT_NAME})
target_include_libc_header_files(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE gcc)
