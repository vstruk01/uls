#include "uls.h"

void mx_sort_dir_alp(t_dir *dir) {
    for (t_dir *i = dir; i; i = i->next) {
        for (t_dir *j = dir; j->next; j = j->next) {
            if (mx_strcmp(j->cnst->name, j->next->cnst->name) > 0) {
                t_const *tmp = j->cnst;
                char *name = j->name;

                j->name = j->next->name;
                j->next->name = name;
                j->cnst = j->next->cnst;
                j->next->cnst = tmp;
            }
        }
    }
}
