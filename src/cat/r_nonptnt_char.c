#ifndef PRINT_FILE_C
#define PRINT_FILE_C

#include "gcat.h"

void r_nonprnt_char(char *line, ssize_t *line_len, Flags *flags) {
  for (ssize_t i = 0; i < *line_len; i++) {
    int tmp = line[i];
    int not_include_ntc = line[i] != '\n' && line[i] != '\t';

    if ((flags->flag_e || flags->flag_E) && line[i] == '\n') {
      putchar('$');
      tmp = line[i];
    }

    if ((flags->flag_t || flags->flag_T) && line[i] == '\t') {
      putchar(SPEC_SYMBOL_PREFIX);
      tmp = line[i] + SPEC_SYMBOL_STEP;
    }

    if (flags->flag_v) {
      if (line[i] > 0 && line[i] < 32 && not_include_ntc) {
        putchar(SPEC_SYMBOL_PREFIX);
        tmp = line[i] + SPEC_SYMBOL_STEP;
      }

      if (tmp > 127 && tmp < 160) {
        putchar('M');
        putchar('-');
        putchar(SPEC_SYMBOL_PREFIX);
        tmp = line[i] + SPEC_SYMBOL_STEP;
      }

      if (tmp == 127) {
        putchar(SPEC_SYMBOL_PREFIX);
        tmp = '?';
      }
    }

    printf("%c", tmp);
  }
}

#endif