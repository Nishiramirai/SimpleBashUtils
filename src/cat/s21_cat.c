#include "s21_cat.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_info(argv[0]);
        return FUNC_ERR_CODE;
    }

    for (int i = 1; i < argc; i++) {
        s21_cat(argv[i]);
    }
    
}

void print_info(char *program_name) {
    printf("Usage: %s [OPTION] [FILE]\n", program_name);
}

int s21_cat(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return FUNC_ERR_CODE;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        printf("%c", c);
    }

    return FUNC_OK_CODE;
}