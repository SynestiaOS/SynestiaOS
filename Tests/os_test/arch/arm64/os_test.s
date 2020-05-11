.section ".text.boot"
.globl _start
_start:
    // Disable extra smp cpus
    mrs x0, mpidr_el1
    and x0, x0, #3
    cmp x0, #0
    b.ne _poweroff

    ldr x0, =__stack
    mov sp, x0

    ldr x0, =__bss_start
    ldr x1, =__bss_end
    bl clean_bss

    bl os_test_main

// todo: implement poweroff
_poweroff:
