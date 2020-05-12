project(BoardRaspberryPi3)

aux_source_directory(${BoardRaspberryPi3_SOURCE_DIR}/src BoardRaspberryPi3Src)
add_library(BoardRaspberryPi3 OBJECT ${BoardRaspberryPi3Src})
target_include_directories(BoardRaspberryPi3 PRIVATE ${BoardRaspberryPi3_SOURCE_DIR}/include)
