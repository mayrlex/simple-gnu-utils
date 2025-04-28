#ifndef PRINT_MATCHED_SUBSTR_C
#define PRINT_MATCHED_SUBSTR_C

#include <stdio.h>

#include "ggrep.h"

void print_matched_substr(char *line, int line_num, char *filename,
                          size_t files_count, regex_t *regex, regmatch_t *match,
                          Flags *flags) {
  const char *tmp_line = line;

  while (regexec(regex, tmp_line, 1, match, 0) == 0) {
    if (files_count > 1 && !flags->h) printf("%s:", filename);
    if (flags->n) printf("%d:", line_num);

    for (int k = match->rm_so; k < match->rm_eo; k++) {
      putchar(tmp_line[k]);
    }

    putchar('\n');

    tmp_line += match->rm_eo;

    if (match->rm_so == match->rm_eo) {
      tmp_line++;
    }
  }
}

#endif