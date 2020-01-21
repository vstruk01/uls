#include "uls.h"

static void strtime(char *tmp, t_const *cnst, t_data *data);

void mx_get_time(struct stat st, t_const *cnst, t_data *data){
    int flag = 1;
    char *tmp = NULL;

    if (flag)
        cnst->time = st.st_mtime;
    else
        cnst->time = st.st_atime;
    tmp = ctime(&cnst->time);
    strtime(tmp, cnst, data);
}

static void strtime(char *tmp, t_const *cnst, t_data *data) {
    time_t now = time(NULL);
    char *new = NULL;

    new = data->flags[6] == 1 ? mx_strnew(20) : mx_strnew(12);
    tmp += 4;
    if (data->flags[6])
        mx_strncpy(new, tmp, 20);
    else if ((now - cnst->time) < MX_HALF_YEAR)
        mx_strncpy(new, tmp, 12);
    else {
        mx_strncpy(new, tmp, 7);
        tmp += 15;
        mx_strcat(new, tmp);
        new[12] = '\0';
    }
    cnst->strtime = new;
}
