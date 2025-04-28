#include "gcat.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    Flags flags = {0};

    int skip_args = 1;
    int is_incorrect_flag = 0;
    int line_num = 0;
    int prev = '\n';

    parse_flags(argc, argv, &flags, &is_incorrect_flag);

    if (is_incorrect_flag) {
      printf(ERR_UNDEFINED_FLAG);
    } else {
      for (int i = skip_args; i < argc; i++) {
        if (argv[i][0] != '-' && strncmp(argv[i], "--", 2) != 0) {
          print_file(&flags, argv[i], &line_num, &prev);
        }
      }
    }
  }

  return 0;
}