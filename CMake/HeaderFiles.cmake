function(target_include_libc_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibC/include)
endfunction()

function(target_include_libelf_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibElf/include)
endfunction()

function(target_include_libmath_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibMath/include)
endfunction()

function(target_include_libgfx_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibGfx/include)
endfunction()

function(target_include_libgui_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibGUI/include)
endfunction()

function(target_include_raspberry_pi_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Board/RaspberryPi/include)
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


function(target_include_application_console_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Applications/Console/include)
endfunction()


function(target_include_module_elfload_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Modules/ELFLoadModule/include)
endfunction()
