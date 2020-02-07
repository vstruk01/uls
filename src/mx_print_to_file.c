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

void mx_print_to_file(char **file, t_data *data) {
    for (int i = 0; i < data->size; i++) {
        if (data->flags[16] && isatty(1) != 0)
            printcolor(file[i], data->cnst);
        mx_printstr(file[i]);
        if (data->flags[16] && isatty(1) != 0)
            mx_printstr(NOCOLOR);
        mx_printstr("\n");
    }
}
