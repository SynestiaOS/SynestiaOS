//
// Created by Shifu Wu  on 2020/7/4.
//

#pragma once

typedef struct FILE {
  // todo: to be done
} FILE;

FILE __stdout;
FILE __stderr;

#define stdout &__stdout
#define stderr &__stderr

int fflush(FILE *);

int fprintf(FILE *file, const char *format, ...);
