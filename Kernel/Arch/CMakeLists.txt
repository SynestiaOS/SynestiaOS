project(KernelArch)

add_executable(KernelImage ${KernelArch_SOURCE_DIR}/${SynestiaArch}/boot.s)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${KernelArch_SOURCE_DIR}/${SynestiaArch}/kernel.ld")
target_link_libraries(KernelImage PRIVATE Kernel LibC BoardRaspberryPi3)
