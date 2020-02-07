#include "uls.h"

static void swap(t_dir *dir) {
    t_const *tmp = dir->cnst;
    char *name = dir->name;

    dir->name = dir->next->name;
    dir->next->name = name;
    dir->cnst = dir->next->cnst;
    dir->next->cnst = tmp;
}

static void sort_size_dir(t_dir *dir) {
    for (t_dir *i = dir; i; i = i->next) {
        for (t_dir *j = dir; j->next; j = j->next) {
            if (j->cnst->size_bytes < j->next->cnst->size_bytes) {
                swap(j);
            }
            else if (j->cnst->size_bytes < j->next->cnst->size_bytes 
                     && mx_strcmp(j->cnst->name, j->next->cnst->name) > 0) {
                swap(j);
            }
        }
    }
}

static void sort_time_dir(t_dir *dir) {
    for (t_dir *i = dir; i; i = i->next) {
        for (t_dir *j = dir; j->next; j = j->next) {
            if (j->cnst->time < j->next->cnst->time)
                swap(j);
            else if (j->cnst->time == j->next->cnst->time 
                     && j->cnst->nsec < j->next->cnst->nsec) {
                swap(j);
            }
            else if (j->cnst->time == j->next->cnst->time
                     && j->cnst->nsec == j->next->cnst->nsec
                     && (mx_strcmp(j->cnst->name, j->next->cnst->name) > 0)) {
                 swap(j);
            }
        }
    }
}

static void sort_revers_dir(t_dir *dir, t_data *data) {
    t_const **tmp = malloc(sizeof (t_const) * (data->size));
    t_dir *save = dir;

    tmp[data->size] = NULL;
    for (int i = 0; i < data->size; i++) {
        tmp[i] = dir->cnst;
        dir = dir->next;
    }
    dir = save;
    for (int i = data->size - 1; i >= 0; i--) {
        dir->cnst = tmp[i];
        dir->name = tmp[i]->name;
        dir = dir->next;
    }
    free(tmp);
}

void mx_sort_dir(t_dir *dir, t_data *data) {
    for (t_dir *i = dir; i != NULL; i = i->next) {
        i->cnst = malloc(sizeof (t_const));
        i->cnst->ful_n = NULL;
        i->cnst->name = i->name;
        mx_get_flag_l(i->cnst, data);
        data->size++;
    }
    if (data->flags[9])
        return;
    if (data->flags[10])
        sort_size_dir(dir);
    else if (data->flags[11])
        sort_time_dir(dir);
    else
        mx_sort_dir_alp(dir);
    if (data->flags[12])
        sort_revers_dir(dir, data);
    dir = data->dir;
}
