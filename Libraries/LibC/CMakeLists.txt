PROJECT(LibC)

aux_source_directory(${LibC_SOURCE_DIR}/src LibCSrc)
add_library(LibC STATIC ${LibCSrc})
target_include_directories(LibC PUBLIC ${LibC_SOURCE_DIR}/include)
target_link_libraries(LibC PRIVATE BoardRaspberryPi3 gcc) # link gcc to use __aeabi_idivmod
