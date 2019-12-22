#include "libmx.h"

static char **cycle(char **arr, int**all,  char *pivot, int *count) {
    while (*all[0] <= *all[1]) {
        while(mx_strlen(arr[*all[0]]) < mx_strlen(pivot))
            (*all[0])++;
        while(mx_strlen(arr[*all[1]]) > mx_strlen(pivot))
            (*all[1])--;
        if (*all[0] <= *all[1]) {
            if (mx_strlen(arr[*all[1]]) != mx_strlen(arr[*all[0]])) {
                char *temp = arr[*all[0]];
                arr[*all[0]] = arr[*all[1]];
                arr[*all[1]] = temp;
                (*count)++;
            }
            (*all)[1]--;
            (*all)[0]++;
        }
    }
    return arr;
}

int mx_quicksort(char **arr, int left, int right){
    int count = 0;
    int *all = malloc(sizeof(int) * 2);

    if(left < right) {
        all[0] = left;
        all[1] = right;
        char *pivot = arr[(all[0] + all[1]) / 2];
        arr = cycle(arr, &all, pivot, &count);
        int i = all[0];
        int j = all[1];

        count += mx_quicksort(arr, left, j);
        count += mx_quicksort(arr, i, right);
    }
    return count;
}
