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
    .word software_insterupt_isp
_prefetch_abort_addr:
    .word prefetch_abort_handler
_data_abort_addr:
    .word data_abort_handler
_unused_addr:
    .word unused_handler
_interrupt_addr:
    .word interupt_isp
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

_reset_cpu0:
    push    {r4, r5, r6, r7, r8, r9}

    ldr     r0, =exception_vector_table

    // set vector address.
    mcr P15, 0, r0, c12, c0, 0

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

    // set vector address.
    mcr P15, 0, r0, c12, c0, 0

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

    // set vector address.
    mcr P15, 0, r0, c12, c0, 0

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

    // set vector address.
    mcr P15, 0, r0, c12, c0, 0

    mov     r1, #0x0000
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8}
    pop     {r4, r5, r6, r7, r8, r9}
    ldr     pc, =_start


.global  current_thread_stack;
.global  switch_thread_stack;
.global  switch_to_signal;

halt_cpu:
    wfi // wait for interrup coming
    b halt_cpu

software_insterupt_isp:
    //cpsr
    stmfd   sp!, {r1-r12,lr}
    
    bl software_interrupt_handler

    ldmfd   sp!, {r1-r12,lr}
    subs    pc,  lr, #0
    nop



interupt_isp:
    //cpsr
    stmfd   sp!, {r0-r12,lr}

    bl interrupt_handler

    //R0: swithch_to_signal Address
    ldr r0, =switch_to_signal
    ldr r1, [r0]

    mov r2, #0
    str r2,[r0]

    cmp r2, r1
    beq just_exit_interrupt

    mov r2, #1
    cmp r2, r1
    beq cpu_save_context

    add sp, sp, #14*4
    b cpu_restore_context

/////////////////////////////////////////////////////////////
//////////  Save Previous Thread Status /////////////////////
/////////////////////////////////////////////////////////////
cpu_save_context:
    //R1: Irq Stack, Save for Pop Previous Registers
    mov r1, sp
    //Save Irq SP to normal SP
    //Restore Irq Stack, Leave Irq State
    add sp, sp, #13*4

    //R0: Irq LR(Thread PC)
    ldmfd sp!, {r0}
    //The LR Should sub 4, because the instruction interruptted has not been execute over
    sub r0, r0, #4

    //R3: Save cpsr
    //Change to Previous State, Disable Irq/Fiq
    mrs r3, spsr
    mov r2, r3
    orr r3,#(1 << 6) | (1 << 7)
    msr cpsr, r3

    //Push r4-r12, lr, pc
    stmfd sp!, {r0}
    stmfd sp!, {r4-r12, lr}

    //Restore r0-r3 to r9-r12
    ldr r9, [r1, #0]
    ldr r10, [r1, #4]
    ldr r11, [r1, #8]
    ldr r12, [r1, #0xc]

    //Push cpsr, r0-r3
    stmfd sp!, {r2, r9-r12}

    //Update Current Thread Stack
    ldr r0, =current_thread_stack   //Pointer **
    ldr r0, [r0]                    //Pointer *
    str sp, [r0]

/////////////////////////////////////////////////////////////
//////////  End of Save Previous Thread Status //////////////
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
//////////  Restore Previous Thread Status //////////////////
/////////////////////////////////////////////////////////////
cpu_restore_context:
    //Restore Sp to New Stack
    ldr r2, =switch_thread_stack    //Pointer **
    ldr r2, [r2]                    //Pointer *
    ldr r2, [r2]                    //Stack

    mov r0,  #0xd3
    msr cpsr_c, r0

    mov sp, r2
    ldmfd sp!, {r12}
    //Enable Irq/Fiq
    bic r12, #(1 << 6) | (1 << 7)
    msr spsr, r12
    ldmfd sp!, {r0-r12, lr, pc}^

/////////////////////////////////////////////////////////////
//////////  End of Restore Previous Thread Status ///////////
/////////////////////////////////////////////////////////////

just_exit_interrupt:
    ldmfd   sp!, {r0-r12,lr}
    subs    pc,  lr, #4
    nop

