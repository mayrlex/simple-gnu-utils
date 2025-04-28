#ifndef IS_DUPE_PATTERN_C
#define IS_DUPE_PATTERN_C

#include <string.h>

#include "ggrep.h"

int is_dupe_pattern(char *pattern, Array_s *patterns) {
  int result = 1;

  for (size_t i = 0; i < patterns->length && result != 0; i++)
    result = strcmp(pattern, patterns->buffer[i]);

  return result;
}

#endif