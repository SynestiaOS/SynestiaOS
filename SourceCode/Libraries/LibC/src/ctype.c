//
// Created by Shifu Wu  on 2020/7/4.
//

#include <ctype.h>
#include <stdlib.h>

const char *__all_printable_characters__ = "0123456789"
                                           "abcdefghijklmnopqrstuvwxyz"
                                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                           "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
                                           " ";

int isprint(int ch) {
  while (*__all_printable_characters__ != '\0') {
    printf("not 0\n");
    if (*__all_printable_characters__++ == ch) {
      return 1;
    }
  }
  return 0;
}
