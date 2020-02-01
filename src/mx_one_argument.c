#include  "uls.h"

void mx_one_argument(t_data *data) {
    if (mx_read_dir(".", data)) {
        if (data->flags[4] || data->flags[5] || data->flags[3])
            mx_print_l(data->cnst, data);
        else {
            if (data->flags[8] && !data->flags[14]) {
                mx_printstr_update("total ",
                data->strtotal, "\n", NULL, NULL);
            }
            if (data->flags[14])
                mx_print_m(data);
            else
                mx_print_file(data);
        }
    }
}
