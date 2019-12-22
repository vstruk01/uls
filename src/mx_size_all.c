#include "uls.h"

int mx_size_a(t_data *data) {
    int col = data->size / data->width; // кількіть колонок

    if (data->size % data->width != 0)
        col++;
    return data->width * col;
}
