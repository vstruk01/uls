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
        if (data->flags[16])
            printcolor(file[i], data->cnst);
        mx_printstr_update(file[i], NOCOLOR, NULL, NULL);
        mx_printstr("\n");
    }
}
