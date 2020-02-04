#include "uls.h"

static int count_data(t_data *data) {
    int count = 0;

    if (data->flags[8])
        count += data->max_len_blocks + 1;
    if (data->flags[7])
        count += data->max_len_ino + 1;
    return count;
}

static int print(t_data *data, t_const *cnst, int count) {
    if (isatty(1) != 0)
        mx_control_char_name(&cnst->name);
    if (count == 0)
        count += mx_strlen(cnst->name) + 2 + count_data(data);
    if (data->flags[7]) {
        mx_print_spase(data->max_len_ino - mx_strlen(cnst->strino));
        mx_printstr_update(cnst->strino, " ", NULL, NULL);
    }
    if (data->flags[8]) {
        mx_print_spase(data->max_len_blocks - mx_strlen(cnst->strblocks));
        mx_printstr_update(cnst->strblocks, " ", NULL, NULL);
    }
    mx_printstr_update(cnst->color, cnst->name, NOCOLOR, NULL);
    if (cnst->next != NULL)
        mx_printstr(", ");
    return count;
}

void mx_print_m(t_data *data) {
    t_const *cnst = data->cnst;
    int count = 0;

    if (isatty(1) == 0)
        data->colums = 80;
    while (cnst != NULL) {
        count = print(data, cnst, count);
        if(cnst->next != NULL) {    
            count += mx_strlen(cnst->next->name) + 2 + count_data(data);
        }
        if (data->colums < count) {
            mx_printstr("\n");
            count = 0;
        }
        cnst = cnst->next;
    }
}
