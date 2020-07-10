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

halt_cpu:
    wfi // wait for interrup coming
    b halt_cpu


interupt_isp:
    stmfd   sp!, {r0-r12,lr}

    bl interrupt_handler

    ldmfd   sp!, {r0-r12,lr}
    subs    pc,  lr, #4

