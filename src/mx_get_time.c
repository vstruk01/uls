#include "uls.h"

static void strtime(char *tmp, t_const *cnst);

void mx_get_time(struct stat st, t_const *cnst){
    int flag = 1;
    char *tmp = NULL;

    if (flag)
        cnst->time = st.st_mtime;
    else
        cnst->time = st.st_atime;
    tmp = ctime(&cnst->time);
    strtime(tmp, cnst);
}

static void strtime(char *tmp, t_const *cnst) {
    time_t now = time(NULL);
    char *new = mx_strnew(12);

    tmp += 4;
    if ((now - cnst->time) < MX_HALF_YEAR)
        mx_strncpy(new, tmp, 12);
    else {
        mx_strncpy(new, tmp, 7);
        tmp += 15;
        mx_strcat(new, tmp);
    }
    cnst->strtime = new;
}
