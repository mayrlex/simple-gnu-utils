#ifndef ARRAY_FREE_C
#define ARRAY_FREE_C

#include <stdlib.h>

#include "ggrep.h"

void array_free(Array_s *array) {
  for (size_t i = 0; i < array->length; i++) {
    free(array->buffer[i]);
  }

  free(array->buffer);

  array->buffer = NULL;
  array->length = 0;
}

#endif