#include "uls.h"

int mx_print_flag_f(char *str, t_data *data) {
    t_const *cnst = data->cnst;

    if (str == NULL)
        return 0;
    while (cnst != NULL) {
        if (mx_strcmp(cnst->name_c, str) == 0) {
            if (data->flags[20] && cnst->flag_f != NULL 
                && cnst->flag_f[0] == '/') {
                mx_printstr(cnst->flag_f);
                return 1;
            }
            if (data->flags[19] && cnst->flag_f != NULL) {
                mx_printstr(cnst->flag_f);
                return 1;
            }
            return 0;
        }
        cnst = cnst->next;
    }
    return 0;
}
