function(target_include_libc_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibC/include)
endfunction()

function(target_include_raspberry_pi3_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Board/RaspberryPi3/include)
endfunction()

function(target_include_kernel_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Kernel/include)
endfunction()

function(target_include_vmm_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Kernel/Arch/${SynestiaArch}/vmm/include)
endfunction()


function(target_include_tests_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Tests/include)
endfunction()
