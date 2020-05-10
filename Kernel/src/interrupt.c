#include <interrupt.h>
#include <stdlib.h>

typedef void (*interrupt_handler_t)(void);

static rpi_irq_controller_t * interrupt_regs;

static interrupt_handler_f handlers[NUM_IRQS];
static interrupt_clearer_f clearers[NUM_IRQS];

extern void move_exception_vector(void);

void register_irq_handler(irq_number_t irq_num, interrupt_handler_f handler, interrupt_clearer_f clearer) {
    print("register_irq_handler\n");
    uint32_t irq_pos;
    if (IRQ_IS_BASIC(irq_num)) {
        irq_pos = irq_num - 64;
        handlers[irq_num] = handler;
        clearers[irq_num] = clearer;
        interrupt_regs->Enable_Basic_IRQs |= (1 << irq_pos);
    }
    else if (IRQ_IS_GPU2(irq_num)) {
        irq_pos = irq_num - 32;
        handlers[irq_num] = handler;
        clearers[irq_num] = clearer;
        interrupt_regs->Enable_IRQs_2 |= (1 << irq_pos);
    }
    else if (IRQ_IS_GPU1(irq_num)) {
        irq_pos = irq_num;
        handlers[irq_num] = handler;
        clearers[irq_num] = clearer;
        interrupt_regs->Enable_IRQs_1 |= (1 << irq_pos);
    }
    else {
        printf("ERROR: CANNOT REGISTER IRQ HANDLER: INVALID IRQ NUMBER: %d\n", irq_num);
    }
    print("register_irq_handler done.\n");
}

void interrupt_init() {
    print("interrupt_init...\n");
    interrupt_regs = (rpi_irq_controller_t *)INTERRUPTS_PENDING;
    bzero(handlers, sizeof(interrupt_handler_f) * NUM_IRQS); // reset all handlers
    bzero(clearers, sizeof(interrupt_clearer_f) * NUM_IRQS);
    interrupt_regs->Disable_Basic_IRQs = 0xffffffff; // disable all interrupts
    interrupt_regs->Disable_IRQs_1 = 0xffffffff;
    interrupt_regs->Disable_IRQs_2 = 0xffffffff;
    //move_exception_vector();
    //ENABLE_INTERRUPTS();
    enable_interrupt();
    print("interrupt_init complete.\n");
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
    int j;
    for (j = 0; j < NUM_IRQS; j++) {
        // If the interrupt is pending and there is a handler, run the handler
	print("interrupt_vector\n");
        if (IRQ_IS_PENDING(interrupt_regs, j)  && (handlers[j] != 0)) {
            clearers[j]();
            //ENABLE_INTERRUPTS();
            enable_interrupt();
            handlers[j]();
            disable_interrupt();
            return;
        }
    }
}

void __attribute__((interrupt("FIQ"))) fast_interrupt_vector(void){

}
