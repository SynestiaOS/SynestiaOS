//
// Created by XingfengYang on 2020/6/12.
//

#ifndef __KERNEL_MM_H__
#define __KERNEL_MM_H__
#include <stdint.h>

/**
 * create memory block after __end_stack segment
 */
void  mm_init();


/**
 * malloc memory block
 * @param size
 * @return
 */
void* kmalloc(uint32_t size);


/**
 * resize memory block
 * @param mem
 * @param size
 * @return
 */
void* krealloc(void *mem, uint32_t size);


/**
 * free memory block
 */
void kfree(void *);

#endif //__KERNEL_MM_H__
