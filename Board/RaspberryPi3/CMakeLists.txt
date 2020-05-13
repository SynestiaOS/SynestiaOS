project(BoardRaspberryPi3)

aux_source_directory(${BoardRaspberryPi3_SOURCE_DIR}/src BoardRaspberryPi3Src)
add_library(BoardRaspberryPi3 STATIC ${BoardRaspberryPi3Src})
target_include_directories(BoardRaspberryPi3 PUBLIC ${BoardRaspberryPi3_SOURCE_DIR}/include)
target_link_libraries(BoardRaspberryPi3 PRIVATE LibC Kernel)