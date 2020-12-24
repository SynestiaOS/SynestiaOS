#include <boot.h>

.section ".text.boot"
.globl _start


/*
 * Helper macro to enter SVC mode cleanly and mask interrupts. reg is
 * a scratch register for the macro to overwrite.
 *
 * This macro is intended for forcing the CPU into SVC mode at boot time.
 * you cannot return to the original mode.
 */
	.macro safe_svcmode_maskall reg:req

	mrs	\reg , cpsr
	eor	\reg, \reg, #0x1A		/* test for HYP mode */
	tst	\reg, #0x1F
	bic	\reg , \reg , #0x1F		/* clear mode bits */
	orr	\reg , \reg , #0xC0 | 0x13	/* mask IRQ/FIQ bits and set SVC mode */
	bne	1f				/* branch if not HYP mode */
	orr	\reg, \reg, #0x100		/* mask Abort bit */
	adr	lr, 2f
	msr	spsr_cxsf, \reg
	.word	0xE12EF30E			/* msr ELR_hyp, lr */
	.word	0xE160006E			/* eret */
1:	msr	cpsr_c, \reg
2:

	.endm

_start:
    safe_svcmode_maskall r0
    mov	r0, #0
    mcr p15, 0, r0, c12, c0, 0	

    //b _goto_kernel_main // init cpu0
    //b _init_cpu0 // init cpu0

    // there are 4 cores within rasberry pi 3, and 4 cores will execute the following code at the same time
    mrc p15, #0, r0, c0, c0, #5 // Move to ARM Register r0 from Coprocessor c0. Read ID Code Register
    and r0, r0, #3 // r0 &= 0x03 core - 1
    cmp r0, #0 // check whether r0==0
    beq _init_cpu0 // init cpu0

    cmp r0, #1 // check whether r0==1
    beq _init_cpu1_new // init cpu1

    //cmp r0, #2 // check whether r0==2
    //beq _init_cpu2 // init cpu2

    //cmp r0, #3 // check whether r0==3
    //beq _init_cpu3 // init cpu3
    ldr pc, =_halt_smp // else, go to _halt_smp, it means only core with id 0,1,2,3 will execute the following code

_init_cpu0:
    safe_svcmode_maskall r0
    ldr sp, =__sys_stack

    ldr r0, =__bss_start
    ldr r1, =__bss_end
    bl  memclean // call memclean(r0, r1)

    cps	#0x13				/* set svc mode */
    ldr	sp, =__svc_stack
    cps	#0x11				/* set fiq mode */
    ldr	sp, =__fiq_stack
    cps	#0x12				/* set irq mode */
    ldr	sp, =__irq_stack
    cps	#0x17				/* set abort mode */
    ldr	sp, =__abort_stack
    cps	#0x1B				/* set "undefined" mode */
    ldr	sp, =__abort_stack
    cps	#0x1F				/* set system mode */
    ldr	sp, =__sys_stack
    b _goto_kernel_main

_init_cpu1:
    safe_svcmode_maskall r0
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

_init_cpu1_new:
    safe_svcmode_maskall r0
    mrc	p15, 0, r0, c0, c0, 5		/* read MPIDR */
    and	r0, r0, #CORES-1		
    mov	r1, #EXCEPTION_STACK_SIZE	/* calculate exception stack offset for core */
    mul	r1, r0, r1
    cps	#0x11				/* set fiq mode */
    ldr	r2, =__fiq_stack
    add	sp, r1, r2
    cps	#0x12				/* set irq mode */
    ldr	r2, =__irq_stack
    add	sp, r1, r2
    cps	#0x17				/* set abort mode */
    ldr	r2, =__abort_stack
    add	sp, r1, r2
    cps	#0x1B				/* set "undefined" mode */
    add	sp, r1, r2
    
    mov	r1, #KERNEL_STACK_SIZE		/* calculate kernel stack offset for core */
    mul	r1, r0, r1
    cps	#0x1F				/* set system mode */
    ldr	r2, =__sys_stack
    add	sp, r1, r2
    b _goto_kernel_main

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
