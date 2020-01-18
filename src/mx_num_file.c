#include "uls.h"

void mx_num_file(t_const *cnst, t_data *data) {
    int num = 0;

    while (cnst != NULL) {
        if (cnst->name != NULL && num < mx_strlen(cnst->name))
            num = mx_strlen(cnst->name);
        cnst = cnst->next;
    }
    num = num + ( 8 - (num % 8));
    data->colums = mx_columns();
    data->max_len_name = num;
    data->width = data->colums / data->max_len_name;
    data->size_all = mx_size_a(data);
}
