#include "ggrep.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ggrep.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    Flags flags = {0};
    Array_s files = ARRAY_S_DEFAULT;
    Array_s patterns = ARRAY_S_DEFAULT;

    handle_args(argc, argv, &files, &patterns, &flags);

    process_line(&files, &patterns, &flags);

    array_free(&files);
    array_free(&patterns);
  }

  return 0;
}