#include "arm/interrupt.h"
#include "raspi2/synestia_os_hal.h"
#include "kernel/interrupt.h"
#include "arm/vmm.h"
#include "libc/string.h"
#include "kernel/log.h"

#define IRQ_NUMS 96

Tick *tick_init(Tick *tick, TickHandler handler, const char *name) {
    tick->handler = handler;
    memset(tick->name, 0, sizeof(tick->name));
    memcpy(tick->name, name, sizeof(tick->name) - 1);
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
    LogInfo("[Interrupt] tick '%s' registered.\n", tick->name)
}

void interrupt_manager_default_un_register_tick(InterruptManager *manager, Tick *tick) {
    klist_remove_node(&tick->node);
}

void interrupt_manager_default_register(InterruptManager *manager, Interrupt interrupt) {
    manager->interrupts[interrupt.interruptNumber].interruptNumber = interrupt.interruptNumber;
    manager->interrupts[interrupt.interruptNumber].handler = interrupt.handler;
    manager->interrupts[interrupt.interruptNumber].clearHandler = interrupt.clearHandler;
    memcpy(manager->interrupts[interrupt.interruptNumber].name, interrupt.name, sizeof(interrupt.name));

    manager->registed[interrupt.interruptNumber] = 1;

    uint32_t interrupt_no = interrupt.interruptNumber;

    synestia_interrupt_enable(interrupt_no);
}

void interrupt_manager_default_unregister(InterruptManager *manager, Interrupt interrupt) {
    manager->interrupts[interrupt.interruptNumber].handler = nullptr;
    manager->interrupts[interrupt.interruptNumber].clearHandler = nullptr;
    manager->registed[interrupt.interruptNumber] = 0;

    uint32_t interrupt_no = interrupt.interruptNumber;

    synestia_interrupt_disable(interrupt_no);
}

void interrupt_manager_default_enable(InterruptManager *manager) {
    if (!arch_is_interrupt_enabled()) {
        arch_enable_interrupt();
        LogInfo("[Interrupt]: enable\n");
    }
}

void interrupt_manager_default_disable(InterruptManager *manager) {
    if (arch_is_interrupt_enabled()) {
        arch_disable_interrupt();
        LogInfo("[Interrupt]: disable\n");
    }
}

void interrupt_manager_default_init(InterruptManager *manager) {
    synestia_init_interrupt();
}

void interrupt_manager_default_tick(InterruptManager *manager) {
    Tick *tick = manager->ticks;
    if (tick != nullptr) {
        LogInfo("[InterruptManager] tick '%s' triggered\n", tick->name);
        tick->handler();
        while (tick->node.next != nullptr) {
            Tick *next = getNode(tick->node.next, Tick, node);
            LogInfo("[InterruptManager] tick '%s' triggered\n", tick->name);
            next->handler();
            tick = next;
        }
    } else {
        LogError("[InterruptManager] no tick registered\n");
    }
}


void interrupt_manager_default_interrupt(InterruptManager *manager) {
    for (uint32_t interrupt_no = 0; interrupt_no < IRQ_NUMS; interrupt_no++) {
        if (manager->registed[interrupt_no] == 1 /* && synestia_interrupt_pending(interrupt_no)*/) {
            LogInfo("[Interrupt]: interrupt '%s' triggered.\n", manager->interrupts[interrupt_no].name);
            if (manager->interrupts[interrupt_no].clearHandler != nullptr) {
                manager->interrupts[interrupt_no].clearHandler();
            }
            manager->interrupts[interrupt_no].handler();
            synestia_interrupt_clear(interrupt_no);
        }
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
    manger->operation.interrupt = (InterruptManagerOperationInterrupt) interrupt_manager_default_interrupt;
    manger->operation.tick = (InterruptManagerOperationTick) interrupt_manager_default_tick;

    manger->ticks = nullptr;
    memset((char *) manger->registed, 0, IRQ_NUMS * sizeof(uint32_t));
    manger->operation.disableInterrupt(manger);

    LogInfo("[InterruptManager] init\n")

    return manger;
}
