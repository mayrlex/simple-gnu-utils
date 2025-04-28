#ifndef HANDLE_ARGS_C
#define HANDLE_ARGS_C

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "ggrep.h"

void handle_args(int argc, char **argv, Array_s *files, Array_s *patterns,
                 Flags *flags) {
  int skip_next_arg = 0;

  if (argv[1][0] != '-') stradd(&argv[1], patterns);

  for (int i = 1; i < argc; i++) {
    if (i + 1 < argc) {
      int is_uniq = is_dupe_pattern(argv[i + 1], patterns) != 0;

      if (strcmp(argv[i], "-e") == 0 && is_uniq) stradd(&argv[i + 1], patterns);

      if (strcmp(argv[i], "-f") == 0)
        handle_pattern_from_file(argv[i + 1], patterns);
    } else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "-f") == 0) {
      fprintf(stderr, "%s: option %s requires an argument\n", LABEL, argv[i]);
    }

    if (is_flag(argv[i])) {
      parse_flags(argv[i], flags);
      skip_next_arg = 1;
    } else if (skip_next_arg) {
      skip_next_arg = 0;
    } else if (i != 1) {
      stradd(&argv[i], files);
    }
  }

  if (flags->is_flags_exists && argc > 2 && !flags->e)
    stradd(&argv[2], patterns);
}

#endif