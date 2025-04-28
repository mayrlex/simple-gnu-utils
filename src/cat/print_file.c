#ifndef PRINT_FILE_C
#define PRINT_FILE_C

#include "gcat.h"

void print_file(Flags *flags, char *filename, int *line_num, int *prev) {
  FILE *file;

  char *line = NULL;
  size_t line_size = 0;
  ssize_t line_len;
  int is_prev_line_empty = 0;

  file = fopen(filename, "r");

  if (file != NULL) {
    while ((line_len = getline(&line, &line_size, file)) != -1) {
      if (flags->is_flags_exists) {
        // Clamp
        int is_line_empty = (line_len == 1 && line[0] == '\n');

        if (flags->flag_s && is_line_empty && is_prev_line_empty) continue;

        is_prev_line_empty = is_line_empty;

        // Line num
        if (((flags->flag_b && line_len > 1) ||
             (flags->flag_n && !flags->flag_b)) &&
            *prev == '\n') {
          printf("%6d\t", ++(*line_num));
        }

        r_nonprnt_char(line, &line_len, flags);

        *prev = line[line_len - 1];
      } else {
        printf("%s", line);
      }
    }

    free(line);
    fclose(file);
  }
}

#endif