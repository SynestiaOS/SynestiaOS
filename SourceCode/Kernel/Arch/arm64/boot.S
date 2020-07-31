.section ".text.boot"
.globl _start
_start:
    // comment out following code because it's halted within exception.S#reset_handler
    // Disable extra smp cpus
    // mrs x0, mpidr_el1
    // and x0, x0, #3
    // cmp x0, #0
    // b.ne _halt_smp

    ldr x0, =__stack
    mov sp, x0

    ldr x0, =__bss_start
    ldr x1, =__bss_end
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
