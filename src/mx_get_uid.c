#include "uls.h"

void mx_get_uid(struct stat st, t_const *cnst) {
    struct passwd *pw = malloc(sizeof(struct passwd *));

    pw = getpwuid(st.st_uid);
    if (pw == NULL)
        cnst->struid = mx_itoa((int)st.st_gid);
    else 
        cnst->struid = pw->pw_name;
}
