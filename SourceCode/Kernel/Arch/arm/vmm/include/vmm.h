//
// Created by XingfengYang on 2020/6/16.
//

#ifndef __KERNEL_VMM_H__
#define __KERNEL_VMM_H__

typedef void (*VirtualMemoryOperationContextSwitch)(struct VirtualMemory *old, struct VirtualMemory* new);

typedef struct VirtualMemoryOperations{
    VirtualMemoryOperationContextSwitch contextSwitch;
} VirtualMemoryOperations;

typedef struct VirtualMemory {
    uint32_t address;


    VirtualMemoryOperations operations;
} VirtualMemory;

void vmm_init();

void vmm_enable();

void vmm_add_map_hook(void (*func)(uint32_t process));

void do_page_fault(uint32_t address);

extern int __PAGE_TABLE;

#endif //__KERNEL_VMM_H__
