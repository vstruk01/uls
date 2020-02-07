#include "uls.h"

int main(int argc, char **argv) {
    t_data *data = malloc(sizeof (t_data));

    mx_read_flags(argv, argc, data);
    if (!data->dir_arr[0])
        mx_one_argument(data);
    else
        mx_many_argument(data);
    system("leaks -q uls");
    if (data->errors)
        return 1;
    return 0;
}
