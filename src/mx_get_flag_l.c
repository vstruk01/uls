#include "uls.h"

void mx_get_flag_l(struct stat st, t_const *cnst) {
    mx_get_blocks(st, cnst); // -s
    mx_get_uid(st, cnst); 
    mx_get_gid(st, cnst);
    mx_get_link(st, cnst);
    mx_get_size_bytes(st, cnst); 
    mx_get_ino(st, cnst); // -i
    mx_get_time(st, cnst); // atime mtime 
    mx_get_law(st, cnst); //permissions
    mx_get_dev(st, cnst); 
    mx_get_rdev(st, cnst); // FOR CHAR SP
    mx_get_minmaj(cnst); // CHAR SP
    mx_get_acl(cnst); // ACL
    // printf("ACL -> %s\n", cnst->stracl);
    // printf("strmin -> %s\n", cnst->strmin);
    // printf("strmaj -> %s\n", cnst->strmaj);
    // printf("maj -> %d\n", cnst->maj);
    // printf("min -> %d\n", cnst->min);
    // printf("strlink -> %s\n", cnst->strlink);
    // printf("gid -> %s\n", cnst->strgid);
    // printf("uid -> %s\n", cnst->struid);
    // printf("bloks -> %lu\n", cnst->blocks);
    // printf("sizebytes -> %lu\n", cnst->size_bytes);
    // printf("ino -> %lu\n", cnst->ino);
    // printf("strtime -> %s\n", cnst->strtime);
    // printf("link -> %lu\n", cnst->link);
    // printf("strrwx -> %s\n", cnst->strrwx);
    // printf("dirname -> %s\n", cnst->dirname);
    // system("leaks -q uls");
}
