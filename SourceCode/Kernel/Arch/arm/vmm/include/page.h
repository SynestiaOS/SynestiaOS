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

typedef struct PageTableEntry {
    uint64_t page_base_address: 22;
    uint64_t implementation_define: 1;
    uint64_t domain: 4;
    uint64_t SBZ: 1;
    uint64_t NS: 1;
    uint64_t PXN: 1;
} PTE __attribute__((packed));


typedef struct PageTable {
    // 512
    PTE pte[512];
} PT;

typedef struct Level2PageTable {
    // 512
    PT *pt;
} L2PT;

typedef struct Level1PageTable {
    // 4
    L2PT *l2Pt;
} L1PT;


typedef struct PhysicalPage {
    uint64_t ref_count:8;
    uint64_t reserved:24;
} PhysicalPage __attribute__((packed));

uint64_t vmm_alloc_page();

uint64_t vmm_free_page(uint64_t page);

#endif // __KERNEL_PAGE_H__
