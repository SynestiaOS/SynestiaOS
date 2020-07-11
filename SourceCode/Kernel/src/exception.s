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
    .word software_interrupt_handler
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
    // Disable extra smp cpus
    mrc p15, #0, r1, c0, c0, #5
    and r1, r1, #3
    cmp r1, #0
    bne halt_cpu

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


interupt_isp:
    //cpsr
    stmfd   sp!, {r0-r12,lr}

    bl interrupt_handler

    ldr r0, =switch_to_signal
    ldr r1, [r0]
    mov r2, #0
    cmp r2, r1

    beq just_exit_interrupt

/////////////////////////////////////////////////////////////
//////////  Save Previous Thread Status /////////////////////
/////////////////////////////////////////////////////////////
    //R0: swithch_to_signal Address
    //R1: Irq Stack, Save for Pop Previous Registers
    ldmfd   sp!, {r6-r12,r5}
    mov r1, sp

    //Save Irq SP to normal SP
    add sp, sp, #14*4

    //R3: Save cpsr
    //Change to Previous State, Disable Irq/Fiq
    mrs r3, spsr
    orr r3, #(1 << 6) | (1 << 7)
    msr cpsr, r3

    //Save pc, lr, r6-r12
    stmfd sp!, {r6-r12, lr, r5}

    //R1: Irq Stack, For pop Previous Registers
    //R2: Save Current SP
    mov r2, sp
    mov sp, r1

    //Save Previous R0-R5
    ldmfd sp!, {r7-r12}
    bic r3, #(1 << 6) | (1 << 7)
    stmfd sp!, {r3,r7-r12}

    //sub r2, r2, #8*4
    //stmfd sp!, {r2, r3,r7-r12}

    //Update Current Thread Stack
    ldr r0, =current_thread_stack
    str sp, [r0]

/////////////////////////////////////////////////////////////
//////////  End of Save Previous Thread Status //////////////
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
//////////  Restore Previous Thread Status //////////////////
/////////////////////////////////////////////////////////////
    //Restore Sp to
    ldr r0, =switch_thread_stack
    ldr r2, [r0]
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

