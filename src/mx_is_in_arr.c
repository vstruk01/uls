#include "uls.h"

int mx_is_in_arr(char *s, char c) {
    for (int i = 0; i < mx_strlen(s); ++i) {
        if (s[i] == c) {
            return 1;
        }
    }
    return 0;
}

