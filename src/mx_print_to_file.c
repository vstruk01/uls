#include "uls.h"

void mx_print_to_file(char **file) {
    for (int i = 0; file[i] != NULL; i++) {
        printf("%s", file[i]);
        printf("\n");
    }
}

