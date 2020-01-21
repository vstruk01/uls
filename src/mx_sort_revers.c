#include "uls.h"

void mx_sort_revers(t_const *cnst, t_data *data) {
    char **tmp = malloc(sizeof(char *) * (data->size + 1));

    tmp[data->size] = NULL;
    for (int i = 0; i < data->size; i++) {
        tmp[i] = cnst->name;
        cnst = cnst->next;
    }
    cnst = data->cnst;
    for (int i = data->size - 1; i >= 0; i--) {
        cnst->name = tmp[i];
        free(cnst->ful_n);
        cnst->ful_n = NULL;
        cnst = cnst->next;
    }
    cnst = data->cnst;
    mx_full_path(data, cnst);
    free(tmp);
}
