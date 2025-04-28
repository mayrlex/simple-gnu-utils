#define _POSIX_C_SOURCE 200809L
#ifndef GCAT_H
#define GCAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LABEL "gcat"
#define ERR_UNDEFINED_FLAG LABEL ": Undefined flag\n"
#define SPEC_SYMBOL_PREFIX '^'
#define SPEC_SYMBOL_STEP 64

typedef struct {
  int flag_b;
  int flag_e;
  int flag_v;
  int flag_E;
  int flag_n;
  int flag_s;
  int flag_t;
  int flag_T;
  int is_flags_exists;
} Flags;

void print_file(Flags *flags, char *filename, int *line_num, int *prev);

void parse_flags(int argc, char **argv, Flags *flags, int *is_incorrect_flag);

void r_nonprnt_char(char *line, ssize_t *line_len, Flags *flags);

#endif