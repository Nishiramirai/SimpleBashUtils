#ifndef CAT_H
#define CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SHORT_OPTS "benstET"

#define OK_CODE 0
#define ERROR_CODE 1

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

void cat();


#endif