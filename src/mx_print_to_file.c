#include "uls.h"

void mx_print_to_file(char **file) {
    for (int i = 0; file[i] != NULL; i++) {
        mx_printstr(file[i]);
        mx_printstr("\n");
    }
}

