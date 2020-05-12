PROJECT(LibC)

aux_source_directory(${LibC_SOURCE_DIR}/src LibCSrc)
add_library(LibC OBJECT ${LibCSrc})
target_include_directories(LibC PRIVATE ${LibC_SOURCE_DIR}/include)
