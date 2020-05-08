#include <interrupt.h>

typedef void (*interrupt_handler_t)(void);

typedef interrupt_handler_t vector_table_t;

__attribute__((section(".interrupt_vector_table")))
const vector_table_t vectors[] = {
    Reset_Handler,
    undefined_instruction,
    software_interrupt,
    prefetch_abort,
    data_abort,
    irq,
    0,
    fiq
};

void interrupt_init() {

}

void enable_interrupt(){

}

void disable_interrupt(){

}

void Reset_Handler(void){
    
}

void undefined_instruction(void){

}

void software_interrupt(void){

}

void prefetch_abort(void){

}

void data_abort(void){

}

void irq(void){

}

void fiq(void){

}