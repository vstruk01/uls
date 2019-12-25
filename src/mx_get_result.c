#include "uls.h"

char **mx_get_result(char **file, t_data *data) {
    char **result = malloc(sizeof(char *) * data->size_all + 1);
    int line = data->size_all / data->width;
    int number = 0;
    int counter = 0;
    int i = 0;

    for (; i <= data->size_all; i++)
        result[i] = NULL;
    for (i = 0; i < data->width; i++) {
        number = i;
        for (int j = 0; j < line; j++) {
            result[number] = file[counter];
            number += data->width;
            counter++;
        }
    }
    return result;
}
