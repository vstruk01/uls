#include "uls.h"

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
}
