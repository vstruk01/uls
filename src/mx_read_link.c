#include "uls.h"

char *mx_read_link(char *dirname) {
    unsigned int size_buf = 50;
    unsigned int tmp_size = 50;
    char *linkstr = NULL;

    while (size_buf == tmp_size) {
        tmp_size += 20;
        char *tmp = mx_strnew(tmp_size);

        size_buf = readlink(dirname, tmp, tmp_size);
        free(tmp);
    }
    linkstr = mx_strnew(size_buf);
    readlink(dirname, linkstr, size_buf);
    return linkstr;
}
