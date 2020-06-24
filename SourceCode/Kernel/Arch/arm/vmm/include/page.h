//
// Created by XingfengYang on 2020/6/15.
//

#ifndef __KERNEL_PAGE_H__
#define __KERNEL_PAGE_H__

#include <stdint.h>

#define KERNEL_L1PT_NUMBER 4
#define KERNEL_L2PT_NUMBER 64
#define KERNEL_PTE_NUMBER 512


#define B 1
#define KB 1024*B
#define MB 1024*KB
#define GB 1024*MB

typedef struct PageTableEntry {
    /* These are used in all kinds of entry. */
    unsigned long valid: 1;      /* Valid mapping */
    unsigned long table: 1;      /* == 1 in 4k map entries too */

    /* These ten bits are only used in Block entries and are ignored in Table entries. */
    unsigned long ai: 3;         /* Attribute Index */
    unsigned long ns: 1;         /* Not-Secure */
    unsigned long user: 1;       /* User-visible */
    unsigned long ro: 1;         /* Read-Only */
    unsigned long sh: 2;         /* Shareability */
    unsigned long af: 1;         /* Access Flag */
    unsigned long ng: 1;         /* Not-Global */

    /* The base address must be appropriately aligned for Block entries */
    unsigned long base: 28;      /* Base address of block or next table */
    unsigned long sbz: 12;       /* Must be zero */

    /* These seven bits are only used in Block entries and are ignored in Table entries. */
    unsigned long hint: 1;       /* In a block of 16 contiguous entries */
    unsigned long pxn: 1;        /* Privileged-XN */
    unsigned long xn: 1;         /* eXecute-Never */
    unsigned long avail: 4;      /* Ignored by hardware */

    /* These 5 bits are only used in Table entries and are ignored in Block entries */
    unsigned long pxnt: 1;       /* Privileged-XN */
    unsigned long xnt: 1;        /* eXecute-Never */
    unsigned long apt: 2;        /* Access Permissions */
    unsigned long nst: 1;        /* Not-Secure */
} PTE __attribute__((packed));


typedef struct PageTable {
    PTE pte[KERNEL_PTE_NUMBER * KERNEL_PTE_NUMBER];
} PT;

typedef struct Level2PageTable {
    PTE pte[KERNEL_PTE_NUMBER];
} L2PT;

typedef struct Level1PageTable {
    PTE pte[KERNEL_L1PT_NUMBER];
} L1PT;


typedef struct PhysicalPage {
    uint64_t ref_count: 8;
    uint64_t reserved: 24;
} PhysicalPage __attribute__((packed));

uint64_t vmm_alloc_page();

uint64_t vmm_free_page(uint64_t page);

#endif // __KERNEL_PAGE_H__
