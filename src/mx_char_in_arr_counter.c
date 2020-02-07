#include "uls.h"


int mx_char_in_arr_counter(char *arr, char c) {
    int counter = 0;
    for (int i = 0; i < mx_strlen(arr); ++i) {
        if (arr[i] == c)
            counter++;
    }
    return counter;
}

