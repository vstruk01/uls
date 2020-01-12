#include "uls.h"

void mx_print_file(char **file, t_data *data) {
    data->width = data->colums / data->num;
    if (isatty(1) == 0)
        mx_print_to_file(file);
    else {
        mx_check_control_char(&file);
        for (int i = 0; i < data->size_all && file != NULL; i++) {
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
}
