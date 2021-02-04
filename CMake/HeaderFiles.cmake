function(target_include_libc_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibC/include)
endfunction()

function(target_include_libstring_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibString/include)
endfunction()

function(target_include_libelf_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibElf/include)
endfunction()

function(target_include_libmath_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibMath/include)
endfunction()

function(target_include_libshell_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibShell/include)
endfunction()

function(target_include_libgfx_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibGfx/include)
endfunction()

function(target_include_libhtml_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibHTML/include)
endfunction()

function(target_include_libbmp_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibBMP/include)
endfunction()

function(target_include_libcss_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibCSS/include)
endfunction()

function(target_include_libgui_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibGUI/include)
endfunction()

function(target_include_libnet_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Libraries/LibNet/include)
endfunction()

function(target_include_raspberry_pi_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Board/RaspberryPi/include)
endfunction()

function(target_include_kernel_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Kernel/include)
endfunction()

function(target_include_arch_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Arch/${SynestiaArch}/include)
endfunction()

function(target_include_tests_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Tests/include)
endfunction()

function(target_include_system_x_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Systems/xd/include)
endfunction()


function(target_include_application_console_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Applications/Console/include)
endfunction()

function(target_include_application_testapp_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Applications/TestApp/include)
endfunction()


function(target_include_module_elfload_header_files Target)
    target_include_directories(${Target} PRIVATE ${SYNESTIAOS_SOURCE_CODE_DIR}/Modules/ELFLoadModule/include)
endfunction()
