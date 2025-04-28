#define _POSIX_C_SOURCE 200809L

#ifndef GGREP_H
#define GGREP_H

#include <regex.h>

#define ARRAY_S_DEFAULT (Array_s){NULL, 0}
#define LABEL "ggrep"
#define NO_FILE "No such file or directory"
#define ERR_REGEX_COMP "RegEx compilation error!"

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int is_flags_exists;
  int is_incorrect_flag;
} Flags;

typedef struct {
  char **buffer;
  size_t length;
} Array_s;

int is_dupe_pattern(char *pattern, Array_s *patterns);
int is_flag(char *arg);
void array_free(Array_s *arr);
void handle_args(int argc, char **argv, Array_s *files, Array_s *patterns,
                 Flags *flags);
void handle_pattern_from_file(char *filename, Array_s *patterns);
void parse_flags(char *argvi, Flags *flags);
void print_line(char *line, int line_num, char *filename, size_t files_count,
                Flags *flags);
void print_matched_substr(char *line, int line_num, char *filename,
                          size_t files_count, regex_t *regex, regmatch_t *match,
                          Flags *flags);
void process_line(Array_s *files, Array_s *patterns, Flags *flags);
void stradd(char **src, Array_s *array_s);
regex_t *compile_patterns(Array_s *patterns, int reg_cflag);

#endif