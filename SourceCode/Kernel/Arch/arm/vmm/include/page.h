//
// Created by XingfengYang on 2020/6/15.
//

#ifndef __KERNEL_PAGE_H__
#define __KERNEL_PAGE_H__

#include <stdint.h>


/**
 * in this arm arch, we use two level page table
 *
 * first level is from bit 20 to bit 31, contains 4094 items;
 * each item can be：
 *  1. invalid
 *  2. a pointer to second level page table
 *  3. 1Mb section
 *  4. 16Mb super section.
 *  5. reserved for LPAE(Large Physical Address Extension)
 *
 *  every page table entry have different struct , you can see from arm official documents
 *
 */

#define B 1
#define KB 1024*B
#define MB 1024*KB
#define GB 1024*MB


typedef struct Level1PageTableEntry {
    uint32_t level2Address;
} L1PTE __attribute__((packed));

typedef struct Level2PageTableEntry {
    uint32_t pageTableAddress;
} L2PTE __attribute__((packed));

typedef struct PageTableEntry {
    uint32_t page_base_address: 22;
    uint32_t implementation_define: 1;
    uint32_t domain: 4;
    uint32_t SBZ: 1;
    uint32_t NS: 1;
    uint32_t PXN: 1;
} PTE __attribute__((packed));


typedef struct Level1PageTable {
    // 4
    L1PTE *l1Pte;
} L1PT;

typedef struct Level2PageTable {
    // 512
    L2PTE *l2Pte;
} L2PT;

typedef struct PageTable {
    // 512
    PTE *pte;
} PT;

#endif // __KERNEL_PAGE_H__
