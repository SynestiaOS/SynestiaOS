.section ".text"
exception_vector_table:
    ldr pc, _reset_addr
    ldr pc, _undefined_instruction_vector_addr
    ldr pc, _software_interrupt_vector_addr
    ldr pc, _prefetch_abort_vector_addr
    ldr pc, _data_abort_vector_addr
    ldr pc, _unused_handler_addr
    ldr pc, _interrupt_vector_addr
    ldr pc, _fast_interrupt_vector_addr

_reset_addr:
    .word reset
_undefined_instruction_vector_addr:
    .word undefined_instruction_vector
_software_interrupt_vector_addr:
    .word software_interrupt_vector
_prefetch_abort_vector_addr:
    .word prefetch_abort_vector
_data_abort_vector_addr:
    .word data_abort_vector
_unused_handler_addr:
    .word unused_handler
_interrupt_vector_addr:
    .word interrupt_vector
_fast_interrupt_vector_addr:
    .word fast_interrupt_vector

reset:
    mov     r0, #0x8000 
    mov     r1, #0x0000  
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}  
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}  
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}  
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}

