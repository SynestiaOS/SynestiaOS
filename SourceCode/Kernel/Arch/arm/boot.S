.section ".text.boot"
.globl _start
_start:
    // there are 4 cores within rasberry pi 3, and 4 cores will execute the following code at the same time
    mrc p15, #0, r0, c0, c0, #5 // Move to ARM Register r0 from Coprocessor c0. Read ID Code Register
    and r0, r0, #0xFF // r0 &= 0xFF
    cmp r0, #0 // check whether r0==0
    beq _init_cpu0 // init cpu0

    cmp r0, #1 // check whether r0==1
    beq _init_cpu1 // init cpu1

    cmp r0, #2 // check whether r0==2
    beq _init_cpu2 // init cpu2

    cmp r0, #3 // check whether r0==3
    beq _init_cpu3 // init cpu3

    ldr pc, =_halt_smp // else, go to _halt_smp, it means only core with id 0,1,2,3 will execute the following code

_init_cpu0:
    ldr sp, =__sys_stack

    ldr r0, =__bss_start
    ldr r1, =__bss_end
    bl  memclean // call memclean(r0, r1)

    mrs r0, cpsr // move coprocessor register cpsr to ARM register r0

    bic r0,     #0x1F // set r0[4:0] to bit 0
    orr r0,     #0x13 // set r0[4], r0[1:0] to bit 1, 0b10011
    msr cpsr_c, r0 // enter SVC (supervisor) mode
    ldr r1,=__svc_stack
    bic sp, r1, #0x7

    bic r0,     #0x1F
    orr r0,     #0x12 // set r0[4], r0[1] to bit 1, 0b10010
    msr cpsr_c, r0 // enter IRQ mode
    ldr r1,=__irq_stack
    bic sp, r1, #0x7

    bic r0,     #0x1F
    orr r0,     #0x11 // set r0[4], r0[0] to bit 1, 0b10001
    msr cpsr_c, r0 // enter FIQ mode
    ldr r1,=__fiq_stack
    bic sp, r1, #0x7

    bic r0,     #0x1F
    orr r0,     #0x13
    msr cpsr_c, r0 // enter SVC (supervisor) mode
    ldr pc, =_goto_kernel_main

_init_cpu1:
    ldr sp, =__sys_stack-0x8000

    mrs r0, cpsr // move coprocessor register cpsr to ARM register r0

    bic r0,     #0x1F // set r0[4:0] to bit 0
    orr r0,     #0x13 // set r0[4], r0[1:0] to bit 1, 0b10011
    msr cpsr_c, r0 // enter SVC (supervisor) mode
    ldr r1,=__svc_stack-0x8000
    bic sp, r1, #0x7

    bic r0,     #0x1F
    orr r0,     #0x12 // set r0[4], r0[1] to bit 1, 0b10010
    msr cpsr_c, r0 // enter IRQ mode
    ldr r1,=__irq_stack-0x8000
    bic sp, r1, #0x7

    bic r0,     #0x1F
    orr r0,     #0x11 // set r0[4], r0[0] to bit 1, 0b10001
    msr cpsr_c, r0 // enter FIQ mode
    ldr r1,=__fiq_stack-0x8000
    bic sp, r1, #0x7

    bic r0,     #0x1F
    orr r0,     #0x13
    msr cpsr_c, r0 // enter SVC (supervisor) mode
    wfe
    ldr pc, =_goto_kernel_main

_init_cpu2:
    ldr sp, =__sys_stack-0x8000-0x8000

    mrs r0, cpsr // move coprocessor register cpsr to ARM register r0

    bic r0,     #0x1F // set r0[4:0] to bit 0
    orr r0,     #0x13 // set r0[4], r0[1:0] to bit 1, 0b10011
    msr cpsr_c, r0 // enter SVC (supervisor) mode
    ldr r1,=__svc_stack-0x8000-0x8000
    bic sp, r1, #0x7

    bic r0,     #0x1F
    orr r0,     #0x12 // set r0[4], r0[1] to bit 1, 0b10010
    msr cpsr_c, r0 // enter IRQ mode
    ldr r1,=__irq_stack-0x8000-0x8000
    bic sp, r1, #0x7

    bic r0,     #0x1F
    orr r0,     #0x11 // set r0[4], r0[0] to bit 1, 0b10001
    msr cpsr_c, r0 // enter FIQ mode
    ldr r1,=__fiq_stack-0x8000-0x8000
    bic sp, r1, #0x7

    bic r0,     #0x1F
    orr r0,     #0x13
    msr cpsr_c, r0 // enter SVC (supervisor) mode
    wfe
    ldr pc, =_goto_kernel_main

_init_cpu3:
    ldr sp, =__sys_stack-0x8000-0x8000-0x8000

    mrs r0, cpsr // move coprocessor register cpsr to ARM register r0

    bic r0,     #0x1F // set r0[4:0] to bit 0
    orr r0,     #0x13 // set r0[4], r0[1:0] to bit 1, 0b10011
    msr cpsr_c, r0 // enter SVC (supervisor) mode
    ldr r1,=__svc_stack-0x8000-0x8000-0x8000
    bic sp, r1, #0x7

    bic r0,     #0x1F
    orr r0,     #0x12 // set r0[4], r0[1] to bit 1, 0b10010
    msr cpsr_c, r0 // enter IRQ mode
    ldr r1,=__irq_stack-0x8000-0x8000-0x8000
    bic sp, r1, #0x7

    bic r0,     #0x1F
    orr r0,     #0x11 // set r0[4], r0[0] to bit 1, 0b10001
    msr cpsr_c, r0 // enter FIQ mode
    ldr r1,=__fiq_stack-0x8000-0x8000-0x8000
    bic sp, r1, #0x7

    bic r0,     #0x1F
    orr r0,     #0x13
    msr cpsr_c, r0 // enter SVC (supervisor) mode
    wfe
    ldr pc, =_goto_kernel_main

_goto_kernel_main:
    #ifndef ENV_KERNEL_UNIT_TESTS
        bl kernel_main
    #else
    #warning "building kernel for unit tests!!!"
        bl kernel_main_tests
    #endif

_halt_smp:
    wfi // wait for interrup coming
    b _halt_smp