#include "./gcat.h"

void parse_flags(int argc, char **argv, Flags *flags, int *is_incorrect_flag) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] != '-') {
      for (size_t j = 1; j < strlen(argv[i]); j++) {
        switch (argv[i][j]) {
          case 'b':
            flags->flag_b = 1;
            flags->is_flags_exists = 1;
            break;
          case 'e':
            flags->flag_e = 1;
            flags->flag_v = 1;
            flags->is_flags_exists = 1;
            break;
          case 'v':
            flags->flag_v = 1;
            flags->is_flags_exists = 1;
            break;
          case 'E':
            flags->flag_E = 1;
            flags->is_flags_exists = 1;
            break;
          case 'n':
            flags->flag_n = 1;
            flags->is_flags_exists = 1;
            break;
          case 's':
            flags->flag_s = 1;
            flags->is_flags_exists = 1;
            break;
          case 't':
            flags->flag_t = 1;
            flags->flag_v = 1;
            flags->is_flags_exists = 1;
            break;
          case 'T':
            flags->flag_T = 1;
            flags->is_flags_exists = 1;
            break;
          default:
            *is_incorrect_flag = 1;
            break;
        }
      }
    }

    if (strncmp(argv[i], "--", 2) == 0) {
      int skip_chars = 2;

      if (strcmp(argv[i] + skip_chars, "number-nonblank") == 0) {
        flags->flag_b = 1;
        flags->is_flags_exists = 1;
      }

      else if (strcmp(argv[i] + skip_chars, "number") == 0) {
        flags->flag_n = 1;
        flags->is_flags_exists = 1;
      }

      else if (strcmp(argv[i] + skip_chars, "squeeze-blank") == 0) {
        flags->flag_s = 1;
        flags->is_flags_exists = 1;
      } else {
        *is_incorrect_flag = 1;
      }
    }
  }
}