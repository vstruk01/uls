#include "uls.h"

void mx_get_flag_l(t_const *cnst) {
    struct stat st;
    
    cnst->ful_n == NULL ? lstat(cnst->name, &st) : lstat(cnst->ful_n, &st);
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
    mx_read_link(cnst);
    // printf("%s", cnst->strrwx); //strrwx 
    // cnst->stracl != NULL ? printf("%s ", cnst->stracl) : printf("  "); //ACL
    // printf("%lu ", cnst->link); //link
    // printf("%s  ", cnst->struid);
    // printf("%s  ", cnst->strgid);
    // printf("%lu ", cnst->size_bytes);
    // printf("%s ", cnst->strtime);
    // printf("%s", cnst->name);
    // if (cnst->strrwx[0] == 'l')
    //     printf(" -> %s", cnst->strlink);
    // printf("\n");
    
    //printf("strmin -> %s\n", cnst->strmin);
    //printf("strmaj -> %s\n", cnst->strmaj);
    //printf("maj -> %d\n", cnst->maj);
    //printf("min -> %d\n", cnst->min);
    // printf("bloks -> %lu\n", cnst->blocks);
    // printf("ino -> %lu\n", cnst->ino);
    // system("leaks -q uls");
}
