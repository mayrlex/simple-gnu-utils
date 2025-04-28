#ifndef STRN_FREE_C
#define STRN_FREE_C

#include <stdlib.h>

#include "ggrep.h"

void strn_free(char ***str, size_t *strs_count) {
  for (size_t i = 0; i < *strs_count; i++) free((*str)[i]);
}

#endif