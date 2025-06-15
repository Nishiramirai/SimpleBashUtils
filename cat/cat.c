#include "cat.h"

int main(int argc, char *argv[]) {
    options_t opts = get_options(argc, argv);
    if (opts.invalid_opt) {
        printf("Invalid options\n");
        return ERROR_CODE;
    }

    if (optind >= argc) {
        cat("stdin");
    } else {
        for (int i = optind; i < argc; i++) {
            cat(argv[optind]);
        }
    }
    
    return OK_CODE;
}


options_t get_options(int argc, char *argv[]) {

    static struct option long_opts[] = {
        {"number-nonblank", 0, 0, 'b'},
        {"number", 0, 0, 'n'},
        {"squezze-blank", 0, 0, 's'},
        {0, 0, 0, 0}
    };

    options_t opts = {0};

    int opt;
    while ((opt = getopt_long(argc, argv, SHORT_OPTS, long_opts, NULL)) != -1) {
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
            opts.squeeze_blank = true;
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

void cat(char *filename) {
    FILE *stream = NULL;

    if (strcmp(filename, "stdin") == 0) {
        stream = stdin;
    } else {
        stream = fopen(filename, "r");
        if (stream == NULL) {
            printf("Can't open file %s\n", filename);
            return;
        }
    }

    int ch;
    while ((ch = fgetc(stream)) != EOF) {
        putchar(ch);
    }

    fclose(stream);
}