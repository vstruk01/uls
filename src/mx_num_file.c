#include "uls.h"

static void get_term(t_data *data, int num) {
    data->colums = mx_columns();
    if (data->flags[16])
        num++;
    else
        num = num + ( 8 - (num % 8));
    data->max_len_name = num;
}

static void get_to_file(t_data *data, int num) {
    data->colums = 80;
    num = num + ( 8 - (num % 8));
    data->max_len_name = num;
}

void mx_num_file(t_const *cnst, t_data *data) {
    int num = 0;

    while (cnst != NULL) {
        if (cnst->name_c != NULL && num < mx_strlen(cnst->name_c))
            num = mx_strlen(cnst->name_c);
        cnst = cnst->next;
    }
    if (data->flags[19] || data->flags[20])
        num++;
    if (isatty(1) != 0)
        get_term(data, num);
    else
        get_to_file(data, num);
    data->strtotal = mx_itoa_sp(data->total);
    data->width = data->colums / data->max_len_name;
    data->size_all = mx_size_a(data);
}
