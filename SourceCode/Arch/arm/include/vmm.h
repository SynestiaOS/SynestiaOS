//
// Created by XingfengYang on 2020/6/16.
//

#ifndef __KERNEL_VMM_H__
#define __KERNEL_VMM_H__

#include "page.h"

typedef struct PageTableEntry {
    /* These are used in all kinds of entry. */
    uint64_t valid: 1; /* Valid mapping */
    uint64_t table: 1; /* == 1 in 4k map entries too */

    /* These ten bits are only used in Block entries and are ignored in Table entries. */
    uint64_t ai: 3; /* Attribute Index */
    uint64_t ns: 1; /* Not-Secure */
    uint64_t user: 1; /* User-visible */
    uint64_t ro: 1; /* Read-Only */
    uint64_t sh: 2; /* Shareability */
    uint64_t af: 1; /* Access Flag */
    uint64_t ng: 1; /* Not-Global */

    /* The base address must be appropriately aligned for Block entries */
    uint64_t base: 28; /* Base address of block or next table */
    uint64_t sbz: 12; /* Must be zero */

    /* These seven bits are only used in Block entries and are ignored in Table entries. */
    uint64_t hint: 1; /* In a block of 16 contiguous entries */
    uint64_t pxn: 1; /* Privileged-XN */
    uint64_t xn: 1; /* eXecute-Never */
    uint64_t avail: 4; /* Ignored by hardware */

    /* These 5 bits are only used in Table entries and are ignored in Block entries */
    uint64_t pxnt: 1; /* Privileged-XN */
    uint64_t xnt: 1; /* eXecute-Never */
    uint64_t apt: 2; /* Access Permissions */
    uint64_t nst: 1; /* Not-Secure */
} __attribute__((packed)) PageTableEntry;

typedef void (*VirtualMemoryOperationContextSwitch)(struct VirtualMemory *old, struct VirtualMemory *new);

typedef void (*VirtualMemoryOperationAllocatePage)(struct VirtualMemory *virtualMemory, uint32_t virtualAddress);

typedef void (*VirtualMemoryOperationMappingPage)(struct VirtualMemory *virtualMemory, uint32_t virtualAddress,
                                                  uint32_t physicalAddress);

typedef void (*VirtualMemoryOperationRelease)(struct VirtualMemory *virtualMemory);

typedef void (*VirtualMemoryOperationEnable)(struct VirtualMemory *virtualMemory);

typedef void (*VirtualMemoryOperationDisable)(struct VirtualMemory *virtualMemory);

typedef uint32_t (*VirtualMemoryOperationTranslateToPhysical)(struct VirtualMemory *virtualMemory, uint32_t address);

typedef uint32_t (*VirtualMemoryOperationGetUserStrLen)(struct VirtualMemory *virtualMemory, void *str);

typedef void *(*VirtualMemoryOperationCopyToKernel)(struct VirtualMemory *virtualMemory, char *src, char *dest,
                                                    uint32_t size);

typedef struct VirtualMemoryOperations {
    VirtualMemoryOperationContextSwitch contextSwitch;
    VirtualMemoryOperationAllocatePage allocatePage;
    VirtualMemoryOperationMappingPage mappingPage;
    VirtualMemoryOperationRelease release;
    VirtualMemoryOperationEnable enable;
    VirtualMemoryOperationDisable disable;
    VirtualMemoryOperationCopyToKernel copyToKernel;
    VirtualMemoryOperationTranslateToPhysical translateToPhysical;
    VirtualMemoryOperationGetUserStrLen getUserStrLen;
} VirtualMemoryOperations;

typedef struct VirtualMemory {
    PageTableEntry *pageTable;
    VirtualMemoryOperations operations;
    PhysicalPageAllocator *physicalPageAllocator;
} VirtualMemory;

KernelStatus vmm_create(VirtualMemory *virtualMemory, struct PhysicalPageAllocator *physicalPageAllocator);

void do_page_fault(uint32_t address);

#endif //__KERNEL_VMM_H__
