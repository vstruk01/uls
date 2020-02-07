#include "uls.h"

char **mx_strarr(int number_of_str, char **argv) {
    
    char **arr = (char **)malloc((number_of_str + 1) * sizeof(char *));
    arr[number_of_str] = NULL;
    for (int i = 0; i < number_of_str;i++) {
    	arr[i] = mx_strdup(argv[i]);
    }

    return arr;
}
