#include "s21_grep.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Not enough arguments\n");
        return FUNC_ERROR_CODE;
    }

    options_t opts = get_options(argc, argv);

    if (optind >= argc - 1) {
        printf("Not enough arguments\n");
        return FUNC_ERROR_CODE;
    }

    
    char *pattern = argv[optind];
    for (int i = optind + 1; i < argc; i++) {
        s21_grep(argv[i], pattern);
    }

    return FUNC_OK_CODE;
}

void s21_grep(char *filename, char *pattern) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Can't open file %s\n", filename);
        return;
    }


    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }


    fclose(file);
    free(line);
}


options_t get_options(int argc, char *argv[]) {

    const char *opts_list = "e:ivcln";

    options_t opts = {0};

    int opt;
    while ((opt = getopt(argc, argv, opts_list)) != -1) {
        switch (opt)
        {
        case 'e':
            opts.pattern = true;
            // TODO: Store pattern
            break;

        case 'i':
            opts.ignore_case = true;
            break;

        case 'v':
            opts.invert_match = true;
            break;

        case 'c':
            opts.linecount_only = true;
            break;

        case 'l':
            opts.filenames_only = true;
            break;

        case 'n':
            opts.number_lines = true;
            break;

        case '?':
            break;
        
        default:
            break;
        }
    }


    return opts;
}