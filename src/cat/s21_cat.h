

#include <getopt.h>
#include <stdio.h>
#include <stdbool.h>


#define FUNC_OK_CODE 0
#define FUNC_ERR_CODE 1


typedef struct {
    bool number_nonblank;
    bool show_ends;
    bool number_lines;
    bool squeeze_blank;
    bool show_tabs;
    bool show_nonprinting;
    bool invalid_opt;
} options_t;


options_t get_options(int argc, char *argv[]);
void s21_cat(char *filename, options_t opts);

void print_info(char *program_name);