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
    uint32_t base_addr;
    uint32_t offset;
} PAE;

typedef struct Level3PageTable {
    PAE pae[512];
} L3PT;

typedef struct Level2PageTable {
    L3PT l3Pt[512];
} L2PT;

typedef struct Level1PageTable {
    L2PT l2Pt[4];
} L1PT;
#endif // __KERNEL_PAGE_H__
