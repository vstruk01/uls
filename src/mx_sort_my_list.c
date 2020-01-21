#include "uls.h"

static void pathname(t_data *data, t_const *data_l);

void mx_sort_my_list(t_const *data_l, t_data *data) {
    for (int i = 0; i < data->size_list; i++) {
        data_l = data->cnst;
        while (data_l->next != NULL) {
            if (mx_strcmp(data_l->name, data_l->next->name) > 0) {
                char *tmp = data_l->name;

                data_l->name = data_l->next->name;
                data_l->next->name = tmp;
            }
            data_l = data_l->next;
        }
    }
    data_l = data->cnst;
    pathname(data, data_l);
    data->strtotal = mx_itoa(data->total);
}

static void pathname(t_data *data, t_const *data_l) {
    while (data_l != NULL) {
        if (data->path !=  NULL) {
            char *tmp = mx_strjoin(data->path, "/");
            data_l->ful_n = mx_strjoin(tmp, data_l->name);
            free(tmp);
        }
        else
            data_l->ful_n = NULL;
        mx_get_flag_l(data_l, data);
        data_l = data_l->next;
    }
}
