#include "uls.h"

void mx_sort_all(t_data *data, t_const *cnst) {
    if (data->flags[9])
        return;
    mx_sort_my_list(cnst, data);
    mx_full_path(data, cnst);
    if (data->flags[10])
        mx_sort_size(data, cnst);
    else if (data->flags[11])
        mx_sort_time(cnst, data);
    if (data->flags[12])
        mx_sort_revers(cnst, data);
}
