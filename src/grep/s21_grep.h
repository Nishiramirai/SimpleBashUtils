#define _GNU_SOURCE

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FUNC_OK_CODE 0
#define FUNC_ERROR_CODE 1

typedef struct {
    bool pattern;               // -e
    bool ignore_case;           // -i
    bool invert_match;          // -v
    bool linecount_only;        // -c
    bool filenames_only;        // -l
    bool number_lines;          // -n

} options_t;

options_t get_options(int argc, char *argv[]);
void s21_grep(char *filename, char *pattern);