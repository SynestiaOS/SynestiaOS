#ifndef __KERNEL_INTERRUPT_H__
#define __KERNEL_INTERRUPT_H__

#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "list.h"

typedef void (*TickHandler)(void);

typedef struct Tick {
    TickHandler handler;
    ListNode node;
} Tick;

Tick *tick_init(Tick *tick, TickHandler handler);

typedef void (*InterruptHandler)(void);

typedef void (*InterruptClearHandler)(void);

typedef struct Interrupt {
    uint32_t interruptNumber;
    InterruptHandler handler;
    InterruptClearHandler clearHandler;
} Interrupt;

typedef void (*InterruptManagerOperationRegisterTick)(struct InterruptManager *manager, Tick *tick);

typedef void (*InterruptManagerOperationUnRegisterTick)(struct InterruptManager *manager, Tick *tick);

typedef void (*InterruptManagerOperationRegister)(struct InterruptManager *manager, Interrupt interrupt);

typedef void (*InterruptManagerOperationUnRegister)(struct InterruptManager *manager, Interrupt interrupt);

typedef void (*InterruptManagerOperationEnableInterrupt)(struct InterruptManager *manager);

typedef void (*InterruptManagerOperationDisableInterrupt)(struct InterruptManager *manager);

typedef void (*InterruptManagerOperationInit)(struct InterruptManager *manager);

typedef void (*InterruptManagerOperationTick)(struct InterruptManager *manager);

typedef struct InterruptManagerOperation {
    InterruptManagerOperationInit init;
    InterruptManagerOperationRegister registerInterrupt;
    InterruptManagerOperationUnRegister unRegisterInterrupt;
    InterruptManagerOperationRegisterTick registerTick;
    InterruptManagerOperationUnRegisterTick unRegisterTick;
    InterruptManagerOperationEnableInterrupt enableInterrupt;
    InterruptManagerOperationDisableInterrupt disableInterrupt;
    InterruptManagerOperationTick tick;
} InterruptManagerOperation;

#define IRQ_NUMS 96
typedef struct InterruptManager {
    Interrupt interrupts[IRQ_NUMS];
    bool registed[IRQ_NUMS];
    Tick *ticks;
    InterruptManagerOperation operation;
} InterruptManager;

InterruptManager *interrupt_manager_create(InterruptManager *manger);

#endif// __KERNEL_INTERRUPT_H__
