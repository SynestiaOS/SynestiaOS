project(Kernel)

aux_source_directory(${Kernel_SOURCE_DIR}/src KernelSrc)
add_library(Kernel STATIC ${KernelSrc} ${Kernel_SOURCE_DIR}/src/exception.s)
target_include_directories(Kernel PUBLIC ${Kernel_SOURCE_DIR}/include)
target_link_libraries(Kernel PRIVATE BoardRaspberryPi3 LibC)

add_subdirectory(${Kernel_SOURCE_DIR}/Arch)
