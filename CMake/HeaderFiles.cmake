function(target_include_libc_header_files Target)
    target_include_directories(${Target} PRIVATE ${CMAKE_SOURCE_DIR}/Libraries/LibC/include)
endfunction()

function(target_include_raspberry_pi3_header_files Target)
    target_include_directories(${Target} PRIVATE ${CMAKE_SOURCE_DIR}/Board/RaspberryPi3/include)
endfunction()

function(target_include_kernel_header_files Target)
    target_include_directories(${Target} PRIVATE ${CMAKE_SOURCE_DIR}/Kernel/include)
endfunction()
