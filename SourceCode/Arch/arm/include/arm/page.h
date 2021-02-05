//
// Created by XingfengYang on 2020/6/15.
//

#ifndef __KERNEL_PAGE_H__
#define __KERNEL_PAGE_H__

#include "kernel/type.h"
#include "libc/stdint.h"

#define KERNEL_L1PT_NUMBER 4
#define KERNEL_L2PT_NUMBER 512
#define KERNEL_PTE_NUMBER 512

#define PAHE_TABLE_SIZE 0x805000
#define PHYSICAL_PAGE_NUMBERS (1 << 20)
#define PAGE_SIZE 4 * KB

#define VA_OFFSET 12
#define KERNEL_PHYSICAL_START 0
#define KERNEL_PHYSICAL_SIZE 256 * MB
#define USER_PHYSICAL_START 256 * MB
#define USER_PHYSICAL_SIZE 512 * MB - USER_PHYSICAL_START

typedef enum PhysicalPageType {
    PAGE_UNKNOWD = 0,
    PAGE_4K,
    PAGE_2M,
} PhysicalPageType;

typedef enum PhysicalPageUsage {
    USAGE_UNKNOWD = 0,
    USAGE_NORMAL,
    USAGE_KERNEL,
    USAGE_KERNEL_HEAP,
    USAGE_USER,
    USAGE_USER_HEAP,
    USAGE_PERIPHERAL,
    USAGE_FRAMEBUFFER,
    USAGE_PAGE_TABLE,
} PhysicalPageUsage;

typedef struct PhysicalPage {
    uint64_t ref_count: 8;
    PhysicalPageType type: 8;
    PhysicalPageUsage usage: 8;
    uint64_t reserved: 8;
} __attribute__((packed)) PhysicalPage;

typedef int64_t (*PhysicalPageAllocatorOperationAllocPage4K)(struct PhysicalPageAllocator *pageAllocator,
                                                             PhysicalPageUsage usage);

typedef uint64_t (*PhysicalPageAllocatorOperationFreePage4K)(struct PhysicalPageAllocator *pageAllocator,
                                                             uint64_t page);

typedef uint64_t (*PhysicalPageAllocatorOperationAllocPage2M)(struct PhysicalPageAllocator *pageAllocator,
                                                              PhysicalPageUsage usage);

typedef uint64_t (*PhysicalPageAllocatorOperationFreePage2M)(struct PhysicalPageAllocator *pageAllocator,
                                                             uint64_t page);

typedef uint64_t (*PhysicalPageAllocatorOperationAllocPage4KAt)(struct PhysicalPageAllocator *pageAllocator,
                                                                PhysicalPageUsage usage, uint64_t address);

typedef uint64_t (*PhysicalPageAllocatorOperationAllocPage2MAt)(struct PhysicalPageAllocator *pageAllocator,
                                                                PhysicalPageUsage usage, uint64_t address);

typedef uint64_t (*PhysicalPageAllocatorOperationPage4KMarkAsUsed)(struct PhysicalPageAllocator *pageAllocator,
                                                                   uint64_t page);

typedef uint64_t (*PhysicalPageAllocatorOperationPage4KMarkAsFree)(struct PhysicalPageAllocator *pageAllocator,
                                                                   uint64_t page);

typedef uint64_t (*PhysicalPageAllocatorOperationAllocHugeAt)(struct PhysicalPageAllocator *pageAllocator,
                                                              PhysicalPageUsage usage, uint64_t page, uint32_t size);

typedef uint64_t (*PhysicalPageAllocatorOperationFreeHugeAt)(struct PhysicalPageAllocator *pageAllocator, uint64_t page,
                                                             uint32_t size);

typedef struct PhysicalPageAllocatorOperations {
    PhysicalPageAllocatorOperationAllocPage4K allocPage4K;
    PhysicalPageAllocatorOperationAllocPage2M allocPage2M;
    PhysicalPageAllocatorOperationFreePage4K freePage4K;
    PhysicalPageAllocatorOperationFreePage2M freePage2M;
    PhysicalPageAllocatorOperationAllocPage4KAt allocPage4KAt;
    PhysicalPageAllocatorOperationAllocPage2MAt allocPage2MAt;
    PhysicalPageAllocatorOperationAllocHugeAt allocHugeAt;
    PhysicalPageAllocatorOperationFreeHugeAt freeHugeAt;
    PhysicalPageAllocatorOperationPage4KMarkAsUsed page4KMarkAsUsed;
    PhysicalPageAllocatorOperationPage4KMarkAsFree page4KMarkAsFree;
} PhysicalPageAllocatorOperations;

typedef struct PhysicalPageAllocator {
    uint32_t base;
    uint32_t size;
    PhysicalPage physicalPages[PHYSICAL_PAGE_NUMBERS];// TODO: should be size/pagesize
    uint32_t physicalPagesUsedBitMap[PHYSICAL_PAGE_NUMBERS / BITS_IN_UINT32];
    PhysicalPageAllocatorOperations operations;
} PhysicalPageAllocator;

KernelStatus page_allocator_create(PhysicalPageAllocator *pageAllocator, uint32_t base, uint32_t size);

#endif// __KERNEL_PAGE_H__
