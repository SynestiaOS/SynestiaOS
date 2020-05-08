#include <interrupt.h>

typedef void (*interrupt_handler_t)(void);

typedef union {
    interrupt_handler_t isr;
    void *stack_top;
} vector_table_t;

__attribute__((section(".interrupt_vector_table")))
const vector_table_t vectors[] = {
    {.stack_top = &__stack}, // 0    Pointer to top of Stack
    Reset_Handler,              // 1    Reset handler is called when the <RESET> button is pressed
    NMI_Handler,                // 2    Non-Maskable Interrupt handler
    HardFault_Handler,          // 3    Hard Fault Handler
    MemManage_Handler,          // 4    Memory management fault Handler
    BusFault_Handler,           // 5    Bus Fault Handler
    UsageFault_Handler,         // 6    Usage Fault Handler
    0,                          // 7    Reserved
    0,                          // 8    Reserved
    0,                          // 9    Reserved
    0,                          // 10   Reserved
    SVC_Handler,                // 11   SuperVisor Call Handler
    DebugMon_Handler,           // 12   Debug Monitor Handler
    0,                          // 13   Reserved
    PendSV_Handler,             // 14   Pendeable interrupt driven request
    SysTick_Handler,            // 15   SysTick Timer handler
};

void interrupt_init() {

}

void enable_interrupt(){

}

void disable_interrupt(){

}

void Reset_Handler(void){
    
}

void SysTick_Handler(void){

}

void PendSV_Handler(void){

}

void NMI_Handler(void){

}

void MemManage_Handler(void){

}

void BusFault_Handler(void){

}

void UsageFault_Handler(void){

}

void HardFault_Handler(void){

}

void SVC_Handler(void){

}

void DebugMon_Handler(void){

}