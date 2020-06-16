//
// Created by XingfengYang on 2020/6/15.
//

#include <page.h>
#include <vmm.h>


#define KERNEL_PHYSICAL_START 3*128*MB
#define PAGE_SIZE 4*KB

#define PAGE_TABLE_SIZE 4*MB

L1PT *l1Pt;

void map_kernel_mm() {
    int pageTablePhysicalAddress = &__PAGE_TABLE;
    l1Pt = (L1PT *) pageTablePhysicalAddress;

    // map the first level 1 entry
    l1Pt->l1Pte = (L1PTE *) pageTablePhysicalAddress;
    l1Pt->l1Pte[0].level2Address = pageTablePhysicalAddress + 3 * sizeof(L1PTE);

    // map 512 level 2 entry
    L2PT *l2Pt = (L2PT *) l1Pt->l1Pte[0].level2Address;
    for (uint32_t i = 0; i < 512; i++) {
        l2Pt->l2Pte = (L1PTE *) l1Pt->l1Pte[0].level2Address + i * sizeof(L2PTE);
        l2Pt->l2Pte[i].pageTableAddress = l1Pt->l1Pte[0].level2Address + 512 * sizeof(L2PTE) + i * 512 * sizeof(PTE);
    }

    // map 64 * 512 page table entry
    uint32_t index = 0;
    for (uint32_t i = 0; i < 64; i++) {
        l2Pt->l2Pte = (L1PTE *) l1Pt->l1Pte[0].level2Address + i * sizeof(L2PTE);
        PTE* pte = (PTE*)l2Pt->l2Pte[i].pageTableAddress;

        for(uint32_t j = 0;j<512;j++){
            pte[j].page_base_address = ((KERNEL_PHYSICAL_START + index * PAGE_SIZE) & 0xFFFFF000) >> 12;
            // todo: other page table entry option bits
            index++;
        }
    }

}

void init_vmm() {
    map_kernel_mm();
}

void enable_vm() {

}

