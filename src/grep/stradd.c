#ifndef STR_ADD_C
#define STR_ADD_C
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ggrep.h"

void stradd(char **src, Array_s *array) {
  char **tmp = realloc(array->buffer, (array->length + 1) * sizeof(char *));

  if (tmp != NULL) {
    array->buffer = tmp;

    array->buffer[array->length++] = strdup(*src);
  }
}

#endif