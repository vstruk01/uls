#include "uls.h"

static void printcolor(char *str, t_const *cnst) {
    while (cnst != NULL) {
        if (mx_strcmp(cnst->name_c, str) == 0) {
            if (cnst->color != NULL)
                mx_printstr(cnst->color);
            return;
        }
        cnst = cnst->next;
    }
}

static void printspase(int i) {
    for (int j = 0; j < i; j++)
        mx_printchar(' ');
}


void mx_print_file(t_data *data) {
    char **file = data->name_all;

    if (data->isattyflag == 1 || data->flags[2])
        mx_print_to_file(file, data);
    else {
        mx_check_control_char(&file);
        for (int i = 0; i < data->size_all && file != NULL; i++) {
            if (i % data->width == 0 && i != 0)
                mx_printstr("\n");
            if (file[i] != NULL) {
                if (data->flags[16])
                    printcolor(file[i], data->cnst);
                mx_printstr_update(file[i], NOCOLOR, NULL, NULL);
                if ((i + 1) % data->width != 0 && file[i + 1] != NULL)
                    printspase(data->max_len_name - mx_strlen(file[i]));
            }
        }
        if (data->size != 0)
            mx_printstr("\n");
    }
}
