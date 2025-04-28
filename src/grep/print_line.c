#ifndef PRINT_LINE_C
#define PRINT_LINE_C

#include <stdio.h>

#include "ggrep.h"

void print_line(char *line, int line_num, char *file, size_t files_count,
                Flags *flags) {
  int print_file = file != NULL && (files_count > 1 || flags->l) && !flags->h;
  int print_number = line_num > 0 && !flags->l && (flags->c || flags->n);
  int print_line = line != NULL && !flags->c && !flags->l;

  if (print_file) printf("%s", file);
  if ((print_file && print_number) ||
      (print_file && print_line && !print_number))
    putchar(':');
  if (print_number) printf("%d", line_num);
  if (print_number && print_line) putchar(':');
  if (print_line) printf("%s", line);
}

#endif