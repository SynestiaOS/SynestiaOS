//
// Created by XingfengYang on 2020/6/15.
//

#include "arm/kernel_vmm.h"
#include "arm/mmu.h"
#include "arm/page.h"
#include "kernel/log.h"
#include "kernel/type.h"
#include "libc/stdlib.h"

extern int __PAGE_TABLE;
extern PhysicalPageAllocator kernelPageAllocator;

Level1PageTable *kernelVMML1PT;

void map_kernel_pt(uint64_t pageTablePhysicalAddress) {
    int i;
    kernelVMML1PT = (Level1PageTable *) pageTablePhysicalAddress;
    uint64_t* lpae_level1 = (uint64_t*) pageTablePhysicalAddress;
    uint64_t* lpae_level2 = (uint64_t*) (pageTablePhysicalAddress +0x1000);
    lpae_level1[0] = (uint32_t)lpae_level2 | 0x3;
    lpae_level1[1] = 0x40000741;
    lpae_level1[2] = 0x80000741;
    lpae_level1[3] = 0xC0000741;
    for(i = 0; i < 512; i++)
    {
        lpae_level2[i] = 0x0000074D + 0x00200000*i;
    }

}

void map_kernel_mm() {
    uint64_t pageTablePhysicalAddress = (uint64_t) &__PAGE_TABLE;

    map_kernel_pt(pageTablePhysicalAddress);
    LogInfo("[vmm]: page table done\n");
}

void kernel_vmm_init() {
    mmu_disable();
    map_kernel_mm();

    /**
   * if lpaeSupport = 5, means LPAE is supported
   */
    uint32_t lpaeSupport = (read_mmfr0() & 0xF);
    LogWarn("[LPAE]: mmfr0: %d\n", lpaeSupport);

    kernel_vmm_enable();
}

void kernel_vmm_enable() {
    write_primapr(0xff440400);
    LogInfo("[vmm]: Primary Remap Registe writed\n");

    write_ttbcr(0xb0003500);
    LogInfo("[vmm]: ttbcr writed\n");

    write_ttbr0((uint32_t) kernelVMML1PT);
    LogInfo("[vmm]: ttbr0 writed\n");

    mmu_enable();
    LogInfo("[vmm]: vmm enabled\n");
}

PageTableEntry *kernel_vmm_get_page_table() { return (PageTableEntry *) kernelVMML1PT; }

void kernel_vmm_map(uint32_t virtualAddress) {
    LogError("[vmm]: ooops, memory fault at %d .\n", virtualAddress);
}
