//
// Created by XingfengYang on 2021/1/25.
//

#ifndef SYNESTIAOS_GIC_H
#define SYNESTIAOS_GIC_H

#include "libc/stdint.h"

typedef struct InterruptControllerTypeRegister {
    uint32_t ITLinesNumber: 5;
    uint32_t CPUNumber: 3;
    uint32_t Reserved1: 2;
    uint32_t SecurityExtn: 1;
    uint32_t LSPI: 5;
    uint32_t Reserved2: 16;
} InterruptControllerTypeRegister;

typedef struct DistributorImplementerIdentificationRegister {
    uint32_t Implementer: 12;
    uint32_t Revision: 4;
    uint32_t Variant: 4;
    uint32_t Reserved: 4;
    uint32_t ProductID: 8;
} DistributorImplementerIdentificationRegister;

typedef struct PrivatePeripheralInterruptStatusRegister {
    uint32_t Reserved1: 9;
    uint32_t PPI6: 1;
    uint32_t PPI5: 1;
    uint32_t PPI4: 1;
    uint32_t PPI0: 1;
    uint32_t PPI1: 1;
    uint32_t PPI2: 1;
    uint32_t PPI3: 1;
    uint32_t Reserved2: 16;
} PrivatePeripheralInterruptStatusRegister;

typedef struct Distributor {

} Distributor;


typedef struct CPUInterfaceIdentificationRegister {
    uint32_t Implementer: 12;
    uint32_t Revision: 4;
    uint32_t ArchitectureVersion: 4;
    uint32_t ProductID: 12;
} CPUInterfaceIdentificationRegister;

typedef struct VGICTypeRegister {
    uint32_t ListRegs: 6;
    uint32_t Reserved: 20;
    uint32_t PREbits: 3;
    uint32_t PRIbits: 3;
} VGICTypeRegister;

typedef struct CPUInterface {

} CPUInterface;

typedef struct GenericInterruptControllerV2 {
    uint32_t GICD_CTLR; // 0x0
    uint32_t GICD_TYPER; // 0x4
    uint32_t GICD_IIDR; //0x8
    uint32_t UNUSED[30]; //0xc-0x80
    uint32_t GICD_IGROUPRn[15];// 0x080-0x0BC
    uint32_t GICD_ISENABLERn[15];

} GenericInterruptControllerV2;


#endif //SYNESTIAOS_GIC_H
