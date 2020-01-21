#include "uls.h"

static void get_size(t_const *cnst);

void mx_sort_size(t_data *data, t_const *cnst) {
    get_size(cnst);
    for (int i = 0; i < data->size - 1; i++) {
        cnst = data->cnst;
        for (int j = 0; j < data->size - i - 1; j++) {
            if (cnst->size_bytes < cnst->next->size_bytes) {
                char *tmp = cnst->name;
                int sizetmp = cnst->size_bytes;

                cnst->name = cnst->next->name;
                cnst->size_bytes = cnst->next->size_bytes;
                cnst->next->name = tmp;
                cnst->next->size_bytes = sizetmp;   
            }
            cnst = cnst->next;
        }
    }
    cnst = data->cnst;
    mx_full_path(data, cnst);
}

static void get_size(t_const *cnst) {
    struct stat st; 

    while (cnst != NULL) {
        cnst->ful_n == NULL ? lstat(cnst->name, &st) : lstat(cnst->ful_n, &st);
        cnst->size_bytes = st.st_size;
        free(cnst->ful_n);
        cnst->ful_n = NULL;
        cnst = cnst->next;
    }
}
