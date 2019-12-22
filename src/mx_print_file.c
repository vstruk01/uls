#include "uls.h"

void mx_print_file(char **file, t_data *data) {
    data->width = data->colums / data->num;
    for (int i = 0; i < data->size_all; i++) {
        if (i % data->width == 0 && i != 0)
            printf("\n");
        if (file[i] != NULL) {
            printf("%s", file[i]);
            if ((i + 1) % data->width != 0 && file[i + 1] != NULL)    
                for (int j = mx_strlen(file[i]); j < data->num; j++)
                    printf(" ");
        }
    }
    printf("\n");
}
