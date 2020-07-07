//
// Created by XingfengYang on 2020/6/15.
//

#include <page.h>
#include <cache.h>
#include <vmm.h>
#include <stdlib.h>
#include <type.h>

#define KERNEL_PHYSICAL_START 0
#define PAGE_SIZE 4*KB

#define PHYSICAL_PAGE_NUMBERS (1<<20)
#define VA_OFFSET 12

L1PT *kernelVMML1PT;
L2PT *kernelVMML2PT;
PT *kernelVMMPT;

PhysicalPage physicalPages[PHYSICAL_PAGE_NUMBERS];
uint32_t physicalPagesUsedBitMap[PHYSICAL_PAGE_NUMBERS / BITS_IN_UINT32];

uint64_t vmm_alloc_page() {
    for (uint32_t i = 0; i < PHYSICAL_PAGE_NUMBERS / BITS_IN_UINT32; i++) {
        if (physicalPagesUsedBitMap[i] != MAX_UINT_32) {
            for (uint8_t j = 0; j < BITS_IN_UINT32; j++) {
                if ((physicalPagesUsedBitMap[i] & ((uint32_t) 0x1 << j)) == 0) {
                    physicalPages[i * BITS_IN_UINT32 + j].ref_count += 1;
                    physicalPagesUsedBitMap[i] |= (uint32_t) 0x1 << j;
                    return i * BITS_IN_UINT32 + j;
                }
            }
        }
    }
}

uint64_t vmm_free_page(uint64_t pageIndex) {
    if (physicalPages[pageIndex].ref_count > 0) {
        physicalPages[pageIndex].ref_count -= 1;

        uint32_t index = pageIndex / BITS_IN_UINT32;
        uint8_t bitIndex = pageIndex % BITS_IN_UINT32;

        physicalPagesUsedBitMap[index] ^= (uint32_t) 0x1 << bitIndex;
        return pageIndex;
    }
}

void map_kernel_l1pt(uint64_t l1ptPhysicalAddress, uint64_t l2ptPhysicalAddress) {
    kernelVMML1PT = (L1PT *) l1ptPhysicalAddress;
    kernelVMML1PT->pte[0].valid = 1;
    kernelVMML1PT->pte[0].table = 1;
    kernelVMML1PT->pte[0].af = 1;
    kernelVMML1PT->pte[0].base = (uint32_t) l2ptPhysicalAddress >> VA_OFFSET;
}

void map_kernel_l2pt(uint64_t l2ptPhysicalAddress, uint64_t ptPhysicalAddress) {
    kernelVMML2PT = (L2PT *) l2ptPhysicalAddress;
    for (uint32_t i = 0; i < KERNEL_PTE_NUMBER; i++) {
        kernelVMML2PT->pte[i].valid = 1;
        kernelVMML2PT->pte[i].table = 1;
        kernelVMML2PT->pte[i].af = 1;
        kernelVMML2PT->pte[i].base = (uint64_t) (ptPhysicalAddress + i * KERNEL_PTE_NUMBER * sizeof(PTE)) >> VA_OFFSET;
    }
    // Peripheral 16MB 0x3F000000
    for (uint32_t i = 0; i < 8; i++) {
        kernelVMML2PT->pte[504 + i].valid = 1;
        kernelVMML2PT->pte[504 + i].table = 0;
        kernelVMML2PT->pte[504 + i].af = 1;
        kernelVMML2PT->pte[504 + i].base = (0x3F000000 | (i * 2 * MB)) >> VA_OFFSET;
    }

    // VideoBuffer 8M 0x3C100000
    for (uint32_t i = 0; i < 4; i++) {
        kernelVMML2PT->pte[480 + i].valid = 1;
        kernelVMML2PT->pte[480 + i].table = 0;
        kernelVMML2PT->pte[480 + i].af = 1;
        kernelVMML2PT->pte[480 + i].base = (0x3C000000 | (i * 2 * MB)) >> VA_OFFSET;
    }

}

void map_kernel_pt(uint64_t ptPhysicalAddress) {
    kernelVMMPT = (PT *) ptPhysicalAddress;
    uint32_t index = 0;
    for (uint32_t i = 0; i < KERNEL_L2PT_NUMBER; i++) {
        for (uint32_t j = 0; j < KERNEL_PTE_NUMBER; j++) {
            uint64_t physicalPageNumber = vmm_alloc_page();
            kernelVMMPT->pte[index].valid = 1;
            kernelVMMPT->pte[index].table = 1;
            kernelVMMPT->pte[index].af = 1;
            kernelVMMPT->pte[index].base = ((KERNEL_PHYSICAL_START + physicalPageNumber * PAGE_SIZE) & 0x000FFFFF000) >> VA_OFFSET;
            index++;
        }
    }
}

void map_kernel_mm() {
    uint64_t pageTablePhysicalAddress = (uint64_t) &__PAGE_TABLE;

    uint64_t l1ptPhysicalAddress = pageTablePhysicalAddress;
    uint64_t l2ptPhysicalAddress = pageTablePhysicalAddress + 4 * KB;
    uint64_t ptPhysicalAddress = (l2ptPhysicalAddress + KERNEL_PTE_NUMBER * sizeof(PTE));

    map_kernel_l1pt(l1ptPhysicalAddress, l2ptPhysicalAddress);
    printf("[vmm]: level 1 page table done\n");
    map_kernel_l2pt(l2ptPhysicalAddress, ptPhysicalAddress);
    printf("[vmm]: level 2 page table done\n");
    map_kernel_pt(ptPhysicalAddress);
    printf("[vmm]: page table done\n");
}

void vmm_init() {
    mmu_disable();
    map_kernel_mm();

    /**
     * if lpaeSupport = 5, means LPAE is supported
     */
    uint32_t lpaeSupport = (read_mmfr0() & 0xF);
    printf("[LPAE]: mmfr0: %d\n", lpaeSupport);

    vmm_enable();
}

void vmm_enable() {
    write_ttbcr(CONFIG_ARM_LPAE << 31);
    printf("[vmm]: ttbcr writed\n");

    write_ttbr0((uint32_t) kernelVMML1PT);
    printf("[vmm]: ttbr0 writed\n");

    write_dacr(0x55555555);
    printf("[vmm]: dacr writed\n");

    mmu_enable();
    printf("[vmm]: vmm enabled\n");
}

