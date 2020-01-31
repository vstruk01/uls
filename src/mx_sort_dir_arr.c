#include "uls.h"

void mx_sort_dir_arr(t_data *data) {
    data->cnst = malloc(sizeof(t_const));
    data->dir = malloc(sizeof(t_dir));
    data->dir->name = NULL;
    data->cnst->name = NULL;
    data->dir->next = NULL;
    data->cnst->next = NULL;
}
