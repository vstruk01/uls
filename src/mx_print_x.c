#include "uls.h"

static void spase(int i) {
    for (int n = 0; n < i; n++)
        mx_printchar(' ');
}

static void printcolor(char *str, t_const *cnst, t_data *data) {
    while (cnst != NULL) {
        if (mx_strcmp(cnst->name_c, str) == 0) {
            if (data->flags[7]) {
                spase(data->max_len_ino - mx_strlen(cnst->strino));
                mx_printstr(cnst->strino);
            }
            if (data->flags[8]) {
                spase(
                data->max_len_blocks - mx_strlen(cnst->strblocks) + 1);
                mx_printstr_update(cnst->strblocks, " ", NULL, NULL);
            }
            if (cnst->color != NULL)
                mx_printstr(cnst->color);
            mx_printstr(cnst->name);
            return ;
        }
        cnst = cnst->next;
    }
}

static void printspase(int i, t_data *data, char *str) {
    int j = 0;

    i -= mx_print_flag_f(str, data);
    j = i / 8;
    if (i % 8 > 0)
        j++;
    if (data->flags[16] && isatty(1)) {
        for (int n = 0; n < i; n++)
            mx_printchar(' ');
        return ;
    }
    for (int n = 0; n < j; n++)
        mx_printchar('\t');
}

static void print_col(t_data *data, char **file) {
    if (!data->isattyflag)
        mx_check_control_char(&file);
    for (int i = 0; file[i] != NULL && file != NULL; i++) {
        if (i % data->width == 0 && i != 0)
            mx_printstr("\n");
        if (file[i] != NULL) {
            if (data->flags[16] && isatty(1))
                printcolor(file[i], data->cnst, data);
            if (!data->flags[16] || !isatty(1))
                mx_printstr(file[i]);
            if (data->flags[16] && isatty(1))
                mx_printstr(MX_NOCOLOR);
            if ((i + 1) % data->width != 0 && file[i + 1] != NULL) {
                printspase(data->max_len_name - mx_strlen(file[i]),
                           data, file[i]);
            }
            else
                mx_print_flag_f(file[i], data);
        }
    }
}

void mx_print_x(t_data *data) {
    char **file = data->name_all;
    
    print_col(data, file);
    if (data->size != 0)
        mx_printstr("\n");
}
