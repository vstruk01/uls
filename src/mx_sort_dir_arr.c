#include "uls.h"

void mx_sort_dir_arr(t_data *data) {
    int counter = 0;

    data->cnst = malloc(sizeof (t_const));
    data->dir = malloc(sizeof (t_dir));
    data->dir->name = NULL;
    data->cnst->name = NULL;
    data->dir->next = NULL;
    data->cnst->next = NULL;
    for (;data->dir_arr[counter]; counter++);
    if (!data->flags[9])
        mx_sort_file(data->dir_arr, counter);
}
