#ifndef PARSE_FLAGS_C
#define PARSE_FLAGS_C

#include <string.h>

#include "ggrep.h"

void parse_flags(char *argvi, Flags *flags) {
  for (size_t i = 1; i < strlen(argvi); i++) {
    switch (argvi[i]) {
      case 'e':
        flags->e = 1;
        flags->is_flags_exists = 1;
        break;
      case 'i':
        flags->i = 1;
        flags->is_flags_exists = 1;
        break;
      case 'v':
        flags->v = 1;
        flags->is_flags_exists = 1;
        break;
      case 'c':
        flags->c = 1;
        flags->is_flags_exists = 1;
        break;
      case 'l':
        flags->l = 1;
        flags->is_flags_exists = 1;
        break;
      case 'n':
        flags->n = 1;
        flags->is_flags_exists = 1;
        break;
      case 'h':
        flags->h = 1;
        flags->is_flags_exists = 1;
        break;
      case 's':
        flags->s = 1;
        flags->is_flags_exists = 1;
        break;
      case 'f':
        flags->f = 1;
        flags->is_flags_exists = 1;
        break;
      case 'o':
        flags->o = 1;
        flags->is_flags_exists = 1;
        break;
      default:
        flags->is_incorrect_flag = 1;
        break;
    }
  }
}

#endif