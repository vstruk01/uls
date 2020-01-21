#ifndef ULS_H
#define ULS_H

#include <time.h>
#include "libmx.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <sys/errno.h>

#define MX_HALF_YEAR 15768000
#define MX_MINOR(x) ((x) & 0xFFFFFF)
#define MX_MAJOR(x) (((x) >> 24) & 0xFF)

typedef struct s_data_const {
    time_t time;
    char *ful_n;
    char *stracl;
    char *name;
    char *strrwx;
    char *strtime;
    char *strlink;
    char *strgid;
    char *struid;
    char *strmaj;
    char *strmin;
    char *strlinkcount;
    char *strbytes;
    char *strblocks;
    char *strino;
    int min;
    int maj;
    long long ino;
    long rdev;
    long dev;
    long size_bytes;
    long link;
    long blocks;
    struct s_data_const *next;
} t_const;

typedef struct s_big_data {
    t_const *cnst;
    char *strtotal;
    char **name_all;
    char **file;
    int *flags;
    char **argv_dir;
    char **argv_file;
    char **argv;
    char *path;
    bool isattyflag;
    int num_name;
    int flag_n;
    int colums;
    int size;
    int size_all;
    int width;
    int argc;
    int flag;
    int size_list;
    int max_len_name;
    bool flag_minmaj;
    int max_len_uid;
    int max_len_gid;
    int max_len_bytes;
    int max_len_link;
    int max_len_min;
    int max_len_maj;
    int max_len_ino;
    int max_len_blocks;
    bool acl;
    int total;
} t_data;

void mx_control_char_name(char **str);
void mx_check_control_char(char ***str);

void mx_printstr_update(char *str1, char *str2, char *str3,
char *str4, char *str5);
void mx_print_spase(int count);
void mx_sort_my_list(t_const *data_l, t_data *data);
void mx_print_l(t_const *cnst, t_data *data);
void mx_get_flag_l(t_const *cnst, t_data *data);
bool mx_isspecial(t_const *cnst);
bool mx_islink(t_const *cnst);
void mx_get_acl(t_const *cnst);
void mx_get_minmaj(t_const *cnst);
void mx_get_rdev(struct stat st, t_const *cnst);
void mx_get_dev(struct stat st, t_const *cnst);
void mx_get_law(struct stat st, t_const *cnst);
void mx_get_blocks(struct stat st, t_const *cnst);
void mx_get_uid(struct stat st, t_const *cnst);
void mx_get_gid(struct stat st, t_const *cnst);
void mx_get_link(struct stat st, t_const *cnst);
void mx_get_size_bytes(struct stat st, t_const *cnst);
void mx_get_ino(struct stat st, t_const *cnst);
void mx_get_time(struct stat st, t_const *cnst, t_data *data);
void mx_read_link(t_const *cnst);

char *mx_itoa_sp(long long number);
void mx_print_to_file(char **file);
void mx_sort_file(char **str, int size);
int mx_size_a(t_data *data);
char **mx_get_result(char **file, t_data *data);
void mx_print_file_return_dir(t_data *data);
void mx_head_size(t_const *cnst, t_data *data);
int mx_columns();
void mx_print_file(t_data *data);
void mx_num_file(t_const *cnst, t_data *data);
void mx_read_dir(char *dirname, t_data *data);

#endif
