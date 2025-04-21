#include "s21_grep.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Not enough arguments\n");
        return FUNC_ERROR_CODE;
    }

    char *pattern = argv[1];

    for (int i = 2; i < argc; i++) {
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