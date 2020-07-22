//
// Created by XingfengYang on 2020/7/22.
//

#ifndef __KERNEL_LOG_H__
#define __KERNEL_LOG_H__

#define LogError(fmt, arg  ...) printf("\033[31m" fmt"\033[0m" ,##arg );

#define LogInfo(fmt, arg  ...)  printf("\033[32m" fmt"\033[0m" ,##arg );

#define LogWarnning(fmt, arg  ...) printf("\033[33m" fmt"\033[0m" ,##arg );

#endif // __KERNEL_LOG_H__