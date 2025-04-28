#ifndef IS_FLAG_C
#define IS_FLAG_C

#include <stdio.h>

#include "ggrep.h"

int is_flag(char *arg) {
  //
  return arg[0] == '-' && arg[1] != '\0';
}

#endif