#include <interrupt.h>
#include <../../Board/RaspberryPi3/include/uart.h>

typedef void (*interrupt_handler_t)(void);


void interrupt_init() {
    enable_interrupt();
}

void enable_interrupt(){
    __asm__ __volatile__("cpsie i");
}

void disable_interrupt(){
    __asm__ __volatile__("cpsid i");
}

static rpi_irq_controller_t* rpiIRQController = (rpi_irq_controller_t*)RPI_INTERRUPT_CONTROLLER_BASE;
rpi_irq_controller_t* getIRQController(void){
    return rpiIRQController;
}

void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector(void){

}

void __attribute__((interrupt("SWI"))) software_interrupt_vector(void){

}

void __attribute__((interrupt("ABORT"))) prefetch_abort_vector(void){

}

void __attribute__((interrupt("ABORT"))) data_abort_vector(void){

}

void unused_handler(void){

}

void __attribute__((interrupt("IRQ"))) interrupt_vector(void){

}

void __attribute__((interrupt("FIQ"))) fast_interrupt_vector(void){

}