#include "cat.h"

int main(int argc, char *argv[]) {
    options_t opts = get_options(argc, argv);
    if (opts.invalid_opt) {
        printf("Invalid options\n");
        return ERROR_CODE;
    }

    if (optind >= argc) {
        cat("stdin", opts);
    } else {
        for (int i = optind; i < argc; i++) {
            cat(argv[optind], opts);
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

void cat(char *filename, options_t opts) {
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

    int previous_char = '\n';
    int current_char;
    int lines_count = 1;
    int empty_lines = 0;
    int skip_flag = 0;
  
    while ((current_char = fgetc(stream)) != EOF) {
      // s flag
      if (opts.squeeze_blank && current_char == '\n' && previous_char == '\n') {
        empty_lines += 1;
        if (empty_lines > 1) {
          skip_flag = 1;
        }
      } else if (current_char != '\n') {
        empty_lines = 0;
        skip_flag = 0;
      }
      if (!skip_flag) {
        // b flag
        if (opts.number_nonblank && (current_char != '\n') &&
            (previous_char == '\n')) {
          printf("%6d\t", lines_count++);
        }
        // n flag
        if (opts.number_lines && previous_char == '\n') {
          printf("%6d\t", lines_count++);
        }
        // e flag
        if (opts.show_ends && current_char == '\n') {
          putchar('$');
        }
        // t flag
        if (opts.show_tabs && current_char == '\t') {
          putchar('^');
          current_char = 'I';
        }
  
        // v flag or without flags
        if (opts.show_nonprinting && current_char != '\n' &&
            current_char != '\t') {
          unsigned char uc = current_char;
          if (uc < 32) {
            printf("^%c", uc + 64);
          } else if (uc == 127) {
            printf("^%c", '?');
          } else if (uc >= 128 && uc < 160) {
            printf("M-^%c", uc - 64);
          } else if (uc >= 160 && uc < 255) {
            printf("M-%c", uc - 128);
          } else if (uc == 255) {
            printf("M-^?");
          } else {
            printf("%c", uc);
          }
        } else {
          putchar(current_char);
        }
      }
      previous_char = current_char;
    }
  

    if (stream != stdin) {
        fclose(stream);
    }
}