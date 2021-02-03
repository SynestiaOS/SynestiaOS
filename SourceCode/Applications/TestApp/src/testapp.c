//
// Created by XingfengYang on 2020/7/7.
//

//#include "testapp/testapp.h"
#include "libc/stdlib.h"

int main(int argc, char *argv[]) {
    int i = 10;
    while (1) {
        printf("Hello World.\n");
        __asm__("CPSIE I");
    }
}
