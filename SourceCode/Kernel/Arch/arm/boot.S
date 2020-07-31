.section ".text.boot"
.globl _start
_start:
    ; mrc p15, #0, r1, c0, c0, #5
    ; and r1, r1, #3
    ; cmp r1, #0
    ; bne _halt_smp

    ldr sp, =__sys_stack

    ldr r0, =__bss_start
    ldr r1, =__bss_end
    bl  memclean

    mrs r0, cpsr

    bic r0,     #0x1F
    orr r0,     #0x13
    msr cpsr_c, r0
    ldr r1,=__svc_stack
    bic sp, r1, #0x7

    bic r0,     #0x1F
    orr r0,     #0x12
    msr cpsr_c, r0
    ldr r1,=__irq_stack
    bic sp, r1, #0x7

    bic r0,     #0x1F
    orr r0,     #0x11
    msr cpsr_c, r0
    ldr r1,=__fiq_stack
    bic sp, r1, #0x7

    bic r0,     #0x1F
    orr r0,     #0x13
    msr cpsr_c, r0

#ifndef ENV_KERNEL_UNIT_TESTS
    bl kernel_main
#else
#warning "building kernel for unit tests!!!"
    bl kernel_main_tests
#endif

_halt_smp:
    wfi // wait for interrup coming
    b _halt_smp
