//
// Created by Shifu Wu  on 2020/7/4.
//

#include <ctype.h>

const char *__all_printable_characters__ = "0123456789"
                                           "abcdefghijklmnopqrstuvwxyz"
                                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                           "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
                                           " ";

int isprint(int character) {
  const char *ptr = __all_printable_characters__;
  while (*ptr != '\0') {
    if (*ptr++ == character) {
      return 1;
    }
  }
  return 0;
}
