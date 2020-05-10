.section ".text"

.global move_exception_vector
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
    .word irq_handler_asm_wrapper
_fast_interrupt_vector_addr:
    .word fast_interrupt_vector

.extern reset_vector
reset:
    mov     r0, #0x8000 
    mov     r1, #0x0000  
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}  
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}  
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}  
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}

move_exception_vector:
    push    {r4, r5, r6, r7, r8, r9}
    ldr     r0, =exception_vector_table
    mov     r1, #0x0000
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8}
    pop     {r4, r5, r6, r7, r8, r9}
    blx     lr

irq_handler_asm_wrapper:
    sub     lr, lr, #4
    srsdb   sp!, #0x13
    cpsid   if, #0x13
    push    {r0-r3, r12, lr}
    and     r1, sp, #4
    sub     sp, sp, r1
    push    {r1}
    bl      interrupt_vector
    pop     {r1}
    add     sp, sp, r1
    pop     {r0-r3, r12, lr}
    rfeia   sp!
