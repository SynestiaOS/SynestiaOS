#include "arm/interrupt.h"
#include "raspi2/synestia_os_hal.h"
#include "kernel/interrupt.h"
#include "arm/vmm.h"
#include "kernel/log.h"

#define IRQ_NUMS 96

Tick *tick_init(Tick *tick, TickHandler handler) {
    tick->handler = handler;
    tick->node.next = nullptr;
    tick->node.prev = nullptr;
    return tick;
}

void interrupt_manager_default_register_tick(InterruptManager *manager, Tick *tick) {
    if (manager->ticks == nullptr) {
        manager->ticks = tick;
    } else {
        klist_append(&manager->ticks->node, &tick->node);
    }
    LogInfo("[Interrupt] tick registered.\n")
}

void interrupt_manager_default_un_register_tick(InterruptManager *manager, Tick *tick) {
    klist_remove_node(&tick->node);
}

void interrupt_manager_default_register(InterruptManager *manager, Interrupt interrupt) {
    manager->interrupts[interrupt.interruptNumber].handler = interrupt.handler;
    manager->interrupts[interrupt.interruptNumber].clearHandler = interrupt.clearHandler;
    manager->registed[interrupt.interruptNumber] = 1;

    uint32_t interrupt_no = interrupt.interruptNumber;

    synestia_interrupt_register(interrupt_no);
}

void interrupt_manager_default_unregister(InterruptManager *manager, Interrupt interrupt) {
    manager->interrupts[interrupt.interruptNumber].handler = nullptr;
    manager->interrupts[interrupt.interruptNumber].clearHandler = nullptr;
    manager->registed[interrupt.interruptNumber] = 0;
}

void interrupt_manager_default_enable(InterruptManager *manager) {
    arch_enable_interrupt();
}

void interrupt_manager_default_disable(InterruptManager *manager) {
    arch_disable_interrupt();
}

void interrupt_manager_default_init(InterruptManager *manager) {
    synestia_init_interrupt();
}

void interrupt_manager_default_tick(InterruptManager *manager) {
    Tick *tick = manager->ticks;
    if (tick != nullptr) {
        (*tick->handler)();
        while (tick->node.next != nullptr) {
            Tick *next = getNode(tick->node.next, Tick, node);
            next->handler();
            tick = next;
        }
    } else {
        LogError("[InterruptManager] no tick registered\n");
    }
}

InterruptManager *interrupt_manager_create(InterruptManager *manger) {
    manger->operation.init = (InterruptManagerOperationInit) interrupt_manager_default_init;
    manger->operation.registerInterrupt = (InterruptManagerOperationRegister) interrupt_manager_default_register;
    manger->operation.unRegisterInterrupt = (InterruptManagerOperationUnRegister) interrupt_manager_default_unregister;
    manger->operation.enableInterrupt = (InterruptManagerOperationEnableInterrupt) interrupt_manager_default_enable;
    manger->operation.disableInterrupt = (InterruptManagerOperationDisableInterrupt) interrupt_manager_default_disable;
    manger->operation.registerTick = (InterruptManagerOperationRegisterTick) interrupt_manager_default_register_tick;
    manger->operation.unRegisterTick = (InterruptManagerOperationUnRegisterTick) interrupt_manager_default_un_register_tick;
    manger->operation.tick = (InterruptManagerOperationTick) interrupt_manager_default_tick;

    manger->ticks = nullptr;
    manger->operation.disableInterrupt(manger);

    LogInfo("[InterruptMa   nager] init\n")

    return manger;
}
