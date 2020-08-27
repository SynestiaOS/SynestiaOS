//
// Created by XingfengYang on 2020/6/16.
//

#ifndef __KERNEL_VMM_H__
#define __KERNEL_VMM_H__
#include <page.h>

typedef void (*VirtualMemoryOperationContextSwitch)(struct VirtualMemory *old, struct VirtualMemory *new);
typedef void (*VirtualMemoryOperationAllocatePage)(struct VirtualMemory *virtualMemory, uint32_t virtualAddress);
typedef void (*VirtualMemoryOperationMappingPage)(struct VirtualMemory *virtualMemory, uint32_t virtualAddress,
                                                  uint32_t physicalAddress);
typedef void (*VirtualMemoryOperationRelease)(struct VirtualMemory *virtualMemory);
typedef void (*VirtualMemoryOperationEnable)(struct VirtualMemory *virtualMemory);

typedef struct VirtualMemoryOperations {
  VirtualMemoryOperationContextSwitch contextSwitch;
  VirtualMemoryOperationAllocatePage allocatePage;
  VirtualMemoryOperationMappingPage mappingPage;
  VirtualMemoryOperationRelease release;
  VirtualMemoryOperationEnable enable;
} VirtualMemoryOperations;

typedef struct VirtualMemory {
  PageTableEntry *pageTable;
  VirtualMemoryOperations operations;
} VirtualMemory;

void vmm_create(VirtualMemory *virtualMemory);

void vmm_init();

void vmm_enable();

void vmm_add_map_hook(void (*func)(uint32_t process));

void do_page_fault(uint32_t address);

extern int __PAGE_TABLE;

#endif //__KERNEL_VMM_H__
