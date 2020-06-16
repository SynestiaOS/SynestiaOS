//
// Created by XingfengYang on 2020/6/15.
//

#include <page.h>
#include <vmm.h>

#define PAGE_TABLE_SIZE 4*MB
#define KERNEL_PHYSICAL_START 3*128*MB
#define PAGE_SIZE 4*KB

L1PT l1Pt;


void map_kernel_mm(){
    uint32_t index = 0;
    for(uint32_t i = 0;i<64;i++){
        for(uint32_t j = 0;i<512;j++){
            uint32_t physicalAddressOfPage = KERNEL_PHYSICAL_START + (PAGE_SIZE * index);
            l1Pt.l2Pt[0].l3Pt[i].pae[j].page_base_address = (physicalAddressOfPage & 0x3FFFFF);
            index++;
        }
    }
}

void init_vmm(){
    map_kernel_mm();
}

void enable_vm(){

}

