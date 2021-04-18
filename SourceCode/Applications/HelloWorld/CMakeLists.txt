PROJECT(HelloWorld C ASM)

aux_source_directory(${HelloWorld_SOURCE_DIR}/src HelloWorldSrc)

add_executable(${PROJECT_NAME}  $<TARGET_OBJECTS:LibC> ${HelloWorldSrc})

target_include_application_testapp_header_files(${PROJECT_NAME})
target_include_libc_header_files(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE gcc)
