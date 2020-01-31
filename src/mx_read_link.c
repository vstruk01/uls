#include "uls.h"

void mx_read_link(t_const *cnst) {
    unsigned int size_buf = 50;
    unsigned int tmp_size = 50;
    char *name = cnst->ful_n == NULL ? cnst->name : cnst->ful_n;

    while (size_buf == tmp_size) {
        char *tmp = mx_strnew(tmp_size);

        tmp_size += 20;
        size_buf = readlink(name, tmp, tmp_size);
        free(tmp);
        printf("%s\n", tmp);
    }
    cnst->strlink = mx_strnew(size_buf);
    readlink(name, cnst->strlink, size_buf);
}
