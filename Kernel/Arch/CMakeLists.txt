project(KernelArch)

add_executable(Kernel.img ${KernelArch_SOURCE_DIR}/${SynestiaArch}/boot.s)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${KernelArch_SOURCE_DIR}/${SynestiaArch}/kernel.ld")
target_link_libraries(Kernel.img PRIVATE Kernel LibC BoardRaspberryPi3)
