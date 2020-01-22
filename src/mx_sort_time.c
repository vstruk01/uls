#include "uls.h"

static void get_time(t_const *cnst, t_data *data);
static void swap(t_const *cnst);

void mx_sort_time(t_const *cnst, t_data *data) {
    get_time(cnst, data);
    for (int i = 0; i < data->size - 1; i++) {
        cnst = data->cnst;
        for (int j = 0; j < data->size - i - 1; j++) {
            if (cnst->time < cnst->next->time)
                swap(cnst);
            else if (cnst->time == cnst->next->time 
                && cnst->nsec < cnst->next->nsec) {
                swap(cnst);
            }
            cnst = cnst->next;
        }
    }
    cnst = data->cnst;
    mx_full_path(data, cnst);
}

static void swap(t_const *cnst) {
    char *tmp = cnst->name;
    time_t sizetmp = cnst->time;
    long nsec = cnst->nsec;

    cnst->name = cnst->next->name;
    cnst->time = cnst->next->time;
    cnst->nsec = cnst->next->nsec;
    cnst->next->name = tmp;
    cnst->next->time = sizetmp;
    cnst->next->nsec = nsec;
}

static void get_time(t_const *cnst, t_data *data) {
    struct stat st; 

    while (cnst != NULL) {
        cnst->ful_n == NULL ? lstat(cnst->name, &st) : lstat(cnst->ful_n, &st);
        if (data->flags[13]) {
            cnst->nsec = st.st_atimespec.tv_nsec;
            cnst->time = st.st_atime;    
        }
        else {
            cnst->nsec = st.st_mtimespec.tv_nsec;
            cnst->time = st.st_mtime;
        }
        free(cnst->ful_n);
        cnst->ful_n = NULL;
        cnst = cnst->next;
    }
}

