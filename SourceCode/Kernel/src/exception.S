.section ".interrupt_vector_table"
exception_vector_table:
    ldr pc, _reset_addr
    ldr pc, _undefined_instruction_addr
    ldr pc, _software_interrupt_addr
    ldr pc, _prefetch_abort_addr
    ldr pc, _data_abort_addr
    ldr pc, _unused_addr
    ldr pc, _interrupt_addr
    ldr pc, _fast_interrupt_addr

_reset_addr:
    .word reset_handler
_undefined_instruction_addr:
    .word undefined_instruction_handler
_software_interrupt_addr:
    .word software_interrupt_isp
_prefetch_abort_addr:
    .word prefetch_abort_handler
_data_abort_addr:
    .word data_abort_isp
_unused_addr:
    .word unused_handler
_interrupt_addr:
    .word interrupt_isp
_fast_interrupt_addr:
    .word fast_interrupt_handler

reset_handler:
    mrc p15, #0, r0, c0, c0, #5 // Move to ARM Register r0 from Coprocessor c0. Read ID Code Register
    and r0, r0, #3 // r0 &= 0x3
    cmp r0, #0 // check whether r0==0
    beq _reset_cpu0 // reset cpu0

    cmp r0, #1 // check whether r0==1
    beq _reset_cpu1 // reset cpu1

    cmp r0, #2 // check whether r0==2
    beq _reset_cpu2 // reset cpu2

    cmp r0, #3 // check whether r0==3
    beq _reset_cpu3 // reset cpu3

    ldr pc,=halt_cpu


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

_reset_cpu0:
    safe_svcmode_maskall r0
    ldr	    sp, =__svc_stack

    push    {r4, r5, r6, r7, r8, r9}
    ldr     r0, =exception_vector_table
    mcr     P15, 0, r0, c12, c0, 0

    mov     r1, #0x0000
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8}
    pop     {r4, r5, r6, r7, r8, r9}
    ldr     pc, =_start

_reset_cpu1:

    push    {r4, r5, r6, r7, r8, r9}

    ldr     r0, =exception_vector_table
    mcr     P15, 0, r0, c12, c0, 0

    mov     r1, #0x0000
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8}
    pop     {r4, r5, r6, r7, r8, r9}
    ldr     pc, =_start

_reset_cpu2:
    push    {r4, r5, r6, r7, r8, r9}

    ldr     r0, =exception_vector_table
    mcr     P15, 0, r0, c12, c0, 0

    mov     r1, #0x0000
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8}
    pop     {r4, r5, r6, r7, r8, r9}
    ldr     pc, =_start

_reset_cpu3:
    push    {r4, r5, r6, r7, r8, r9}

    ldr     r0, =exception_vector_table
    mcr P15, 0, r0, c12, c0, 0

    mov     r1, #0x0000
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8}
    pop     {r4, r5, r6, r7, r8, r9}
    ldr     pc, =_start

.global  switch_to_signal;

halt_cpu:
    wfi // wait for interrupt coming
    b halt_cpu

software_interrupt_isp:
    //cpsr
    stmfd   sp!, {r1-r12,lr}

    bl software_interrupt_handler

    ldmfd   sp!, {r1-r12,lr}
    subs    pc,  lr, #0
    nop

data_abort_isp:
    //cpsr
    stmfd   sp!, {r1-r12,lr}

	bl    data_abort_handler

	ldmfd   sp!, {r1-r12,lr}
    subs    pc,  lr, #0
    nop


.global  cpu_save_context;
.global  cpu_restore_context;
.global  cpu_switch_mm;

cpu_switch_mm:
    mcr p15, 0, r0, c2, c0, 0
    dsb
    bx      lr

interrupt_isp:
    stmfd   sp!, {r0-r12,lr}
    bl      interrupt_handler
    bl      schd_switch_context
    ldmfd   sp!, {r0-r12,lr}
    subs    pc,  lr, #4

cpu_save_context: // Thread *thread, uint32_t offsetOfStack
    // TODO: r0,r1 already modified.
    stmfd   sp!, {r0-r3}

    mov     r3, sp
    add     r0, r0, r1

    mrs     r1, spsr
    stmfd   sp!, {r1}
    stmfd   sp!, {pc}
    stmfd   sp!, {r4-r12,lr}

    str     sp, [r0]
    mov     sp, r3
    bx      lr

cpu_restore_context: // Thread *thread, uint32_t offsetOfStack
    add     r0, r0, r1
    ldr     r2, [r0]
    mov     sp, r2

    ldmfd   sp!, {r4-r12, lr}
    ldmfd   sp!, {r3}
    ldmfd   sp!, {r3}   // cpsr
    msr     spsr, r3
    ldmfd   sp!, {r0-r3}
    bx      lr

