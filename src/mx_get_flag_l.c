#include "uls.h"

void mx_get_flag_l(struct stat st, t_const *cnst) {
    mx_get_blocks(st, cnst);
    mx_get_uid(st, cnst);
    mx_get_gid(st, cnst);
    mx_get_link(st, cnst);
    mx_get_size_bytes(st, cnst);
    mx_get_ino(st, cnst);
    mx_get_time(st, cnst);
    mx_get_law(st, cnst);
    printf("strlink -> %s\n", cnst->strlink);
    printf("gid -> %s\n", cnst->strgid);
    printf("uid -> %s\n", cnst->struid);
    printf("bloks -> %d\n", cnst->blocks);
    printf("sizebytes -> %d\n", cnst->size_bytes);
    printf("ino -> %d\n", cnst->ino);
    printf("strtime -> %s\n", cnst->strtime);
    printf("link -> %d\n", cnst->link);
    printf("strrwx -> %s\n", cnst->strrwx);
    printf("dirname -> %s\n", cnst->dirname);
    time_t all = st.st_mtime;
    time_t now = time(NULL);
    time_t seconds = 365 * 24 * 60 * 60 / 2;
    printf("%lu\n", (long) seconds);
    printf("%lld\n", (long long)(now-all));
}
