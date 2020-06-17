//
// Created by XingfengYang on 2020/6/15.
//

#include <page.h>
#include <vmm.h>


#define KERNEL_PHYSICAL_START 3*128*MB
#define PAGE_SIZE 4*KB

#define PAGE_TABLE_SIZE 4*MB+8*KB+16*B

L1PT *l1Pt;

#define PHYSICAL_PAGE_NUMBERS 1<<20

PhysicalPage physicalPages[PHYSICAL_PAGE_NUMBERS];

uint32_t vmm_alloc_page(){
    for(uint32_t i = 0;i<PHYSICAL_PAGE_NUMBERS;i++){
        if(physicalPages[i].ref_count==0){
            physicalPages[i].ref_count+=1;
            return i;
        }
    }
}

uint32_t vmm_free_page(uint32_t page){
    for(uint32_t i = 0;i<PHYSICAL_PAGE_NUMBERS;i++){
        if(physicalPages[i].ref_count>0){
            physicalPages[i].ref_count-=1;
            return i;
        }
    }
}

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
    for (uint32_t i = 0; i < 64; i++) {
        l2Pt->l2Pte = (L1PTE *) l1Pt->l1Pte[0].level2Address + i * sizeof(L2PTE);
        PTE* pte = (PTE*)l2Pt->l2Pte[i].pageTableAddress;

        for(uint32_t j = 0;j<512;j++){
            uint32_t physicalPageNumber = vmm_alloc_page();
            pte[j].page_base_address = ((KERNEL_PHYSICAL_START + physicalPageNumber * PAGE_SIZE) & 0xFFFFF000) >> 12;
            // todo: other page table entry option bits
        }
    }

}

void vmm_init() {
    map_kernel_mm();

    vmm_enable();
}

void vmm_enable() {

}

