add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Arch)
# todo: arm64 not fully supported now, add following dir to support arm64
if (ARCH STREQUAL arm)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Board)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Kernel)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Libraries)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Applications)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Tests)
endif ()
