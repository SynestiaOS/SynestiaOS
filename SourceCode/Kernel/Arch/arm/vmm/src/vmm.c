//
// Created by XingfengYang on 2020/6/15.
//

#include <page.h>
#include <vmm.h>

#define PAGE_TABLE_SIZE 4*MB
#define KERNEL_PHYSICAL_START 3*128*MB
#define PAGE_SZIE 4*KB

L1PT l1Pt;

PAE get_page(uint32_t index){
    uint32_t pagePhysicalAddress = KERNEL_PHYSICAL_START + index * PAGE_SZIE;
    PAE pae  = *(PAE*)pagePhysicalAddress;
    return pae;
}

void map_kernel_mm(){
    uint32_t index = 0;
    for(uint32_t i = 0;i<64;i++){
        for(uint32_t j = 0;i<512;j++){
            PAE entry = get_page(index);
            l1Pt.l2Pt[0].l3Pt[i].pae[j] = entry;
            index++;
        }
    }
}

void init_vmm(){
    map_kernel_mm();
}

void enable_vm(){

}

