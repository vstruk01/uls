#include "uls.h"

void mx_sort_file(char ***str, int size) {
    char *tmp = NULL;

    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if ((*str)[j][0] > (*str)[j + 1][0]) {
                tmp = (*str)[j];
                (*str)[j] = (*str)[j + 1];
                (*str)[j + 1] = tmp;
            }
}
