//
// Created by XingfengYang on 2020/6/12.
//

#ifndef __KERNEL_VMM_H__
#define __KERNEL_VMM_H__

#define PAGE_TABLE_SIZE 1024
#define PAGE_ENTRY_SIZE 1024

#include <stdint.h>

typedef struct PageTableEntry{
    uint32_t frame:12;
    uint32_t offset:20;
}PageTableEntry;

typedef struct PageTable{
    PageTableEntry entries[PAGE_ENTRY_SIZE];
}PageTable;

typedef struct PageDirectory{
    PageTable tables[PAGE_TABLE_SIZE];
    void *physicalAddress;
}PageDirectory;


void vmm_init();


#endif //__KERNEL_VMM_H__
