#include "s21_cat.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_info(argv[0]);
        return FUNC_ERR_CODE;
    }

    options_t opts = get_options(argc, argv);
    if (opts.invalid_opt) {
        print_info(argv[0]);
        return FUNC_ERR_CODE;
    }

    if (optind >= argc) {
        printf("File name not specified\n");
        print_info(argv[0]);
        return FUNC_ERR_CODE;
    }

    for (int i = optind; i < argc; i++) {
        s21_cat(argv[i], opts);
    }
    

    return FUNC_OK_CODE;
}

void print_info(char *program_name) {
    printf("Usage: %s [OPTION] [FILE]\n", program_name);
}

void s21_cat(char *filename, options_t opts) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Can't open file %s\n", filename);
        return;
    }

    bool prev_line_blank = false;
    int line_number = 1;
    int prev_ch = '\n';
    int ch;
    while ((ch = fgetc(file)) != EOF) {

        // -s flag
        if (opts.squeeze_blank && ch == '\n' && prev_line_blank) {
            continue;
        }
    
        // -n opt
        if (opts.number_lines && prev_ch == '\n') {
            printf("%6d  ", line_number);
            line_number += 1;
        }
        // -b opt
        else if (opts.number_nonblank && prev_ch == '\n' && ch != '\n') {
            printf("%6d  ", line_number);
            line_number += 1;
        }

        else {
            // -e and -t opts
            if (opts.show_ends && ch == '\n') {
                printf("$\n");
            } else if (opts.show_tabs && ch == '\t') {
                printf("^I");
            } else {
                // Base case
                printf("%c", ch);
            }

        }

        if (prev_ch == '\n' && ch == '\n') {
            prev_line_blank = true;
        } else {
            prev_line_blank = false;
        }
        prev_ch = ch;
    }
}

options_t get_options(int argc, char *argv[]) {
    static struct option long_options[] = {
        {"number-nonblank", no_argument, 0, 'b'},
        {"number", no_argument, 0, 'n'},
        {"squeeze-blank", no_argument, 0, 's'},
        {0, 0, 0, 0}
    };

    const char *opts_list = "benstET";

    options_t opts = {0};

    int opt;
    while ((opt = getopt_long(argc, argv, opts_list, long_options, NULL)) != -1) {
        switch (opt)
        {
        case 'b':
            opts.number_nonblank = true;
            break;

        case 'e':
            opts.show_ends = true;
            opts.show_nonprinting = true;
            break;

        case 'E':
            opts.show_ends = true;
            break;

        case 'n':
            opts.number_lines = true;
            break;

        case 's':
            opts.squeeze_blank = true;
            break;

        case 't':
            opts.show_tabs = true;
            opts.show_nonprinting = true;
            break;

        case 'T':
            opts.show_tabs = true;
            break;

        case '?':
            opts.invalid_opt = true;
            break;
        
        default:
            break;
        }
    }

    return opts;
}