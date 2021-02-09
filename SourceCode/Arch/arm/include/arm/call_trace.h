//
// Created by XingfengYang on 2021/1/8.
//

#include "libc/stdbool.h"

#ifndef SYNESTIAOS_CALL_TRACE_H
#define SYNESTIAOS_CALL_TRACE_H

void dump_calltrace(void);
bool func_is_leaf(unsigned int *instr);

#endif //SYNESTIAOS_CALL_TRACE_H
