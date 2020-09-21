.section ".text.boot"
.globl _start

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
	mcr	p15, 0, r0, c12, c0, 0

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
    ldr sp, =__svc_stack

    ldr r0, =__bss_start
    ldr r1, =__bss_end
    bl  memclean // call memclean(r0, r1)

    cps	#0x11				/* change mode to fiq */
    ldr	sp, =__fiq_stack
    cps	#0x12				/* change mode to irq */
    ldr	sp, =__irq_stack
    cps	#0x17				/* change mode to abort */
    ldr	sp, =__abort_stack
    cps	#0x1B				/* change mode to 'undefined' */
    ldr	sp, =__undefined_stack
    cps	#0x1F				/* set system mode */
    ldr	sp, =__sys_stack

    ldr pc, =_goto_kernel_main

_init_cpu1:
    cps	#0x11				/* change mode to fiq */
    ldr	sp, =__fiq_stack-0x8000
    cps	#0x12				/* change mode to irq */
    ldr	sp, =__irq_stack-0x8000
    cps	#0x17				/* change mode to abort */
    ldr	sp, =__abort_stack-0x8000
    cps	#0x1B				/* change mode to 'undefined' */
    ldr	sp, =__undefined_stack-0x8000
    cps	#0x1F				/* set system mode */
    ldr	sp, =__sys_stack-0x8000

    wfe
    ldr pc, =_goto_kernel_main

_init_cpu2:
    cps	#0x11				/* change mode to fiq */
    ldr	sp, =__fiq_stack-0x8000-0x8000
    cps	#0x12				/* change mode to irq */
    ldr	sp, =__irq_stack-0x8000-0x8000
    cps	#0x17				/* change mode to abort */
    ldr	sp, =__abort_stack-0x8000-0x8000
    cps	#0x1B				/* change mode to 'undefined' */
    ldr	sp, =__undefined_stack-0x8000-0x8000
    cps	#0x1F				/* set system mode */
    ldr	sp, =__sys_stack-0x8000-0x8000

    wfe
    ldr pc, =_goto_kernel_main

_init_cpu3:
    cps	#0x11				/* change mode to fiq */
    ldr	sp, =__fiq_stack-0x8000-0x8000-0x8000
    cps	#0x12				/* change mode to irq */
    ldr	sp, =__irq_stack-0x8000-0x8000-0x8000
    cps	#0x17				/* change mode to abort */
    ldr	sp, =__abort_stack-0x8000-0x8000-0x8000
    cps	#0x1B				/* change mode to 'undefined' */
    ldr	sp, =__undefined_stack-0x8000-0x8000-0x8000
    cps	#0x1F				/* set system mode */
    ldr	sp, =__sys_stack-0x8000-0x8000-0x8000
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
