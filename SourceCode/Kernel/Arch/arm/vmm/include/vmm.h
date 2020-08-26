//
// Created by XingfengYang on 2020/6/16.
//

#ifndef __KERNEL_VMM_H__
#define __KERNEL_VMM_H__

typedef struct VMM {

} VMM;

void vmm_init();

void vmm_enable();

void vmm_add_map_hook(void (*func)(uint32_t process));

extern int __PAGE_TABLE;

#endif //__KERNEL_VMM_H__
