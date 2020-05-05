.section ".text.boot"
.globl _start
_start:
    // Disable extra smp cpus
    mrc p15, #0, r1, c0, c0, #5
    and r1, r1, #3
    cmp r1, #0
    bne _halt_smp

    ldr sp, =__stack

    ldr r0, =__bss_start
    ldr r1, =__bss_end
    bl clean_bss

    bl main

_halt_smp:
    wfi // wait for interrup coming
    b _halt_smp
