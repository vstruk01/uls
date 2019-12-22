#include "uls.h"

char **mx_get_result(char **file, char **result, t_data *data) {
    int line = data->size_all / data->width; // -> кількість назв в одій колонці
    int number = 0;
    int tmp = 0;

    for (int i = 0; i < data->width; i++) {
        number = i;
        for (int j = 0; j < line; j++) {
            result[number] = file[tmp];
            number += data->width;
            tmp++;
        }
    }
    return result;
}
