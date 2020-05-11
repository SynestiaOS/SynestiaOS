#include <interrupt.h>
#include <../../Board/RaspberryPi3/include/uart.h>

typedef void (*interrupt_handler_t)(void);


void init_interrupt() {
    enable_interrupt();
}

void enable_interrupt(){
    __asm__ __volatile__("cpsie i");
}

void disable_interrupt(){
    __asm__ __volatile__("cpsid i");
}

void swi(uint32_t num){
    __asm__ __volatile__("mov r0,%0"::"r" (num));
    __asm__ __volatile__("swi 0x0");
}


static rpi_irq_controller_t* rpiIRQController = (rpi_irq_controller_t*)RPI_INTERRUPT_CONTROLLER_BASE;
rpi_irq_controller_t* getIRQController(void){
    return rpiIRQController;
}


void helloswi() {
    disable_interrupt();
    const char str[] = "hello swi\n\0";
    uint32_t i;
    for (i = 0; i < sizeof(str); i++) {
        uart_putc(str[i]);
    }
    enable_interrupt();
}

void __attribute__((interrupt("UNDEF"))) undefined_instruction_handler(void){

}

void __attribute__((interrupt("SWI"))) software_interrupt_handler(void){
    helloswi();
}

void __attribute__((interrupt("ABORT"))) prefetch_abort_handler(void){

}

void __attribute__((interrupt("ABORT"))) data_abort_handler(void){

}

void unused_handler(void){

}

#define IRQ_IS_BASIC(x) ((x >= 64 ))
#define IRQ_IS_GPU2(x) ((x >= 32 && x < 64 ))
#define IRQ_IS_GPU1(x) ((x < 32 ))
#define IRQ_IS_PENDING(regs, num) ((IRQ_IS_BASIC(num) && ((1 << (num-64)) & regs->IRQ_basic_pending)) || (IRQ_IS_GPU2(num) && ((1 << (num-32)) & regs->IRQ_pending_2)) || (IRQ_IS_GPU1(num) && ((1 << (num)) & regs->IRQ_pending_1)))

void __attribute__((interrupt("IRQ"))) interrupt_handler(void){

}

void __attribute__((interrupt("FIQ"))) fast_interrupt_handler(void){

}
