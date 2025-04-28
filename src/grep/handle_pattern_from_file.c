#ifndef HANDLE_PATTERN_FROM_FILE_C
#define HANDLE_PATTERN_FROM_FILE_C

#include <stdio.h>
#include <stdlib.h>

#include "ggrep.h"

void handle_pattern_from_file(char *filename, Array_s *patterns) {
  FILE *pattern_file = fopen(filename, "r");

  if (pattern_file) {
    fseek(pattern_file, 0, SEEK_END);

    size_t size = ftell(pattern_file);

    rewind(pattern_file);

    char *buffer = malloc(size + 1);

    if (buffer) {
      fread(buffer, 1, size, pattern_file);

      if (is_dupe_pattern(buffer, patterns) != 0) {
        buffer[size] = '\0';

        stradd(&buffer, patterns);
      }

      fclose(pattern_file);
    }

    free(buffer);
  } else {
    printf("%s: %s: %s\n", LABEL, filename, NO_FILE);
  }
}

#endif
