#ifndef COMPILE_PATTERNS_C
#define COMPILE_PATTERNS_C

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#include "ggrep.h"

regex_t *compile_patterns(Array_s *patterns, int reg_cflag) {
  regex_t *regex = NULL;

  regex = realloc(regex, patterns->length * sizeof(regex_t));

  if (regex) {
    for (size_t i = 0; i < patterns->length; i++) {
      if (regcomp(&regex[i], patterns->buffer[i], reg_cflag)) {
        printf("%s", ERR_REGEX_COMP);

        free(regex);
      }
    }
  }

  return regex;
}

#endif