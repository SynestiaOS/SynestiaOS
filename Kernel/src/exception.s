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
    .word interrupt_handler
_fast_interrupt_addr:
    .word fast_interrupt_handler

reset_handler:
    push    {r4, r5, r6, r7, r8, r9}
    ldr     r0, =exception_vector_table
    mov     r1, #0x0000
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8}
    pop     {r4, r5, r6, r7, r8, r9}
    blx     lr

