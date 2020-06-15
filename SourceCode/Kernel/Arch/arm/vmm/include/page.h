//
// Created by XingfengYang on 2020/6/15.
//

#ifndef __KERNEL_PAGE_H__
#define __KERNEL_PAGE_H__

#include <stdint.h>

typedef struct PageTableEntry {
    uint32_t physisAddress;
} PAE;

typedef struct Level3PageTable {
    PAE pae[512];
} L3PT;

typedef struct Level2PageTable {
    L3PT pae[512];
} L2PT;

typedef struct Level1PageTable {
    L2PT l2Pt[4];
} L1PT;


#endif // __KERNEL_PAGE_H__
