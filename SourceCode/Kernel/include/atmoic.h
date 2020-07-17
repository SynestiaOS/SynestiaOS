//
// Created by XingfengYang on 2020/7/17.
//

#ifndef __KERNEL_ATMOIC_H__
#define __KERNEL_ATMOIC_H__
#include <stdint.h>
typedef uint32_t Atmoic;

void atmoic_set(Atmoic *atmoic,uint32_t val);
uint32_t atmoic_get(Atmoic *atmoic);

#endif // __KERNEL_ATMOIC_H__

