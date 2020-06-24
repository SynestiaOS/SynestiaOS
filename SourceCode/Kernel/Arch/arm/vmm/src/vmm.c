//
// Created by XingfengYang on 2020/6/15.
//

#include <page.h>
#include <cache.h>
#include <vmm.h>


#define KERNEL_PHYSICAL_START 0
#define PAGE_SIZE 4*KB

#define PAGE_TABLE_SIZE 4*MB+8*KB+16*B

#define PHYSICAL_PAGE_NUMBERS 1<<20

L1PT *l1Pt;

PhysicalPage physicalPages[PHYSICAL_PAGE_NUMBERS];

uint64_t vmm_alloc_page() {
    for (uint64_t i = 0; i < PHYSICAL_PAGE_NUMBERS; i++) {
        if (physicalPages[i].ref_count == 0) {
            physicalPages[i].ref_count += 1;
            return i;
        }
    }
}

uint64_t vmm_free_page(uint64_t page) {
    for (uint64_t i = 0; i < PHYSICAL_PAGE_NUMBERS; i++) {
        if (physicalPages[i].ref_count > 0) {
            physicalPages[i].ref_count -= 1;
            return i;
        }
    }
}

void map_kernel_mm() {
    uint64_t pageTablePhysicalAddress = (uint64_t) &__PAGE_TABLE;

    l1Pt = (L1PT *) pageTablePhysicalAddress;

    // map the first level 1 entry
    l1Pt->l2Pt = (L2PT *) l1Pt + 4 * sizeof(uint64_t);

    // map 512 level 2 entry
    L2PT *l2Pt = l1Pt->l2Pt;
    for (uint64_t i = 0; i < 512; i++) {
        l2Pt->pt = (PT *) (l2Pt + (512 - i) * sizeof(uint64_t) + i * 512 * sizeof(PTE));
        l2Pt += sizeof(uint64_t);
    }

    // map 64 * 512 page table entry
    l2Pt = l1Pt->l2Pt;
    for (uint64_t i = 0; i < 64; i++) {
        for (uint64_t j = 0; j < 512; j++) {
            uint64_t physicalPageNumber = vmm_alloc_page();
            l2Pt->pt->pte[j].page_base_address = ((KERNEL_PHYSICAL_START + physicalPageNumber * PAGE_SIZE) & 0xFFFFF000) >> 12;
            // todo: other page table entry option bits
        }
        l2Pt += sizeof(uint64_t);
    }
}


void vmm_init() {
    map_kernel_mm();

    vmm_enable();
}


void vmm_enable() {
    write_ttbcr(CONFIG_ARM_LPAE << 31 | 0 << 16 | 0 << 0);

    write_ttbr0((uint32_t) l1Pt);

    write_dacr(0x5);

    mmu_enable();

}

