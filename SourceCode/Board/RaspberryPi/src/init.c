#include "raspi2/interrupt_controller.h"
#include "kernel/log.h"
#include "libc/stdlib.h"
#include "raspi2/timer.h"
#include "raspi2/uart.h"
#include "raspi2/gic400.h"
#include "kernel/module.h"
#include "kernel/interrupt.h"

void raspi2_init_bsp(void) {
    uart_init();
    int mmioBase = PERIPHERAL_BASE;
    LogInfo("[MMIO]: %d \n", mmioBase);
    LogInfo("[HAL]: uart_init complete.\n");

}

__module_init(raspi2_init_bsp, 0);

void raspi2_init_timer(void) {
    LogInfo("[HAL]： timer_init...\n");
    LogInfo("[HAL]: generic_timer_init...\n");
    generic_timer_init();
    LogInfo("[HAL]: generic_timer_init complete.\n");
}

__module_init(raspi2_init_timer, 2);

void raspi2_init_interrupt(void) {
    LogInfo("[HAL] interrupt init\n")
#if defined(RASPI4)
    gic400_init(0xFF840000);
#else
    interrupt_controller_init();
#endif
}


extern InterruptManager genericInterruptManager;
void raspi2_register_physical_init(){
    genericInterruptManager.operation.registerPhysicalInit(&genericInterruptManager, raspi2_init_interrupt);
}

__module_init(raspi2_register_physical_init, 1);
