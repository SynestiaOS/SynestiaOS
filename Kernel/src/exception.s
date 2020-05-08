.extern Reset_Handler
.extern undefined_instruction
.extern software_interrupt
.extern prefetch_abort
.extern data_abort
.extern irq
.extern fiq
 
.section .interrupt_vector_table
exception_vector_table:
    ldr pc,=Reset_Handler
    ldr pc,=undefined_instruction
    ldr pc,=software_interrupt
    ldr pc,=prefetch_abort
    ldr pc,=data_abort
    nop
    ldr pc,=irq
    ldr pc,=fiq