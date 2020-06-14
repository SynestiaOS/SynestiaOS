#include <interrupt.h>
#include <stdlib.h>
#include <synestia_os_hal.h>

void print_splash() {
  const char *str = "   _____                       _   _       \n"
                    "  / ____|                     | | (_)      \n"
                    " | (___  _   _ _ __   ___  ___| |_ _  __ _ \n"
                    "  \\___ \\| | | | '_ \\ / _ \\/ __| __| |/ _` |\n"
                    "  ____) | |_| | | | |  __/\\__ \\ |_| | (_| |\n"
                    " |_____/ \\__, |_| |_|\\___||___/\\__|_|\\__,_|\n"
                    "          __/ |                            \n"
                    "         |___/                          \n";

  print(str);
}

void kernel_main(void) {
  print_splash();

  init_interrupt();

  init_bsp();

  swi(1);

  print("swi works\n");

  swi(2);

  print("swi works\n");

  printf("test:%d\n",12);
}
