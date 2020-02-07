#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len,
                const void *little, size_t little_len) { 
    unsigned char *point1 = (unsigned char *)big;
    unsigned char *point2 = (unsigned char *)little;
    unsigned int flag_n[2];

    flag_n[0] = 0; // flag
    flag_n[1] = 0; // n
    if (big_len == 0 || little_len > big_len || little_len == 0)
        return NULL;
    for (unsigned int i = 0; i < big_len - little_len + 1; i++) {
        flag_n[0] = 0;
        flag_n[1] = 0;
        for (unsigned int j = 0; j < little_len; j++, flag_n[1]++)
            if (point1[flag_n[1]] == point2[j])
                flag_n[0]++;
        if (flag_n[0] == little_len)
            return point1;
        point1++;
    }
    return NULL;
}
