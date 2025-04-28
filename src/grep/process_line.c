#define _POSIX_C_SOURCE 200809L

#ifndef PROCESS_LINE_C
#define PROCESS_LINE_C

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#include "ggrep.h"

void process_line(Array_s *files, Array_s *patterns, Flags *flags) {
  char *line = NULL;
  ssize_t line_len = 0;
  size_t line_size = 0;

  int reg_cflag = flags->i ? REG_ICASE : REG_EXTENDED;
  regex_t *regex = compile_patterns(patterns, reg_cflag);

  for (size_t i = 0; i < files->length; i++) {
    FILE *file = fopen(files->buffer[i], "r");

    int line_num = 0;
    int matched_lines = 0;
    int trottle = 0;

    if (file != NULL) {
      while ((line_len = getline(&line, &line_size, file)) != -1) {
        line_num++;

        for (size_t j = 0; j < patterns->length; j++) {
          regmatch_t match;
          int is_matched = regexec(&regex[j], line, 0, NULL, 0) == 0;

          if (flags->v) is_matched = !is_matched;
          if (flags->o && !flags->c && !flags->v && !flags->l) {
            print_matched_substr(line, line_num, files->buffer[i],
                                 files->length, &regex[j], &match, flags);
          }

          if (is_matched) {
            matched_lines++;

            if (!flags->o && !flags->c && !flags->l) {
              print_line(line, line_num, files->buffer[i], files->length,
                         flags);
            }

            if (flags->l && !trottle) {
              printf("%s\n", files->buffer[i]);

              trottle = 1;
            };

            if (line[line_len - 1] != '\n') printf("\n");
          }
        }
      }

      if (flags->c && !flags->l) {
        if (files->length > 1 && !flags->h)
          printf("%s:%d\n", files->buffer[i], matched_lines);
        else
          printf("%d\n", matched_lines);
      }

      fclose(file);
    } else if (!flags->s) {
      printf("%s: %s: %s\n", LABEL, files->buffer[i], NO_FILE);
    }
  }

  if (line != NULL) {
    free(line);
    line = NULL;
  }

  for (size_t i = 0; i < patterns->length; i++) {
    regfree(&regex[i]);
  }

  free(regex);
}

#endif