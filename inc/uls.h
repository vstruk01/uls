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
    char *stracl;
    char *name;
    char *strrwx;
    char *strtime;
    char *strlink;
    char *strgid;
    char *struid;
    char *strmaj;
    char *strmin;
    int min;
    int maj;
    long ino;
    long rdev;
    long dev;
    long size_bytes;
    long link;
    long blocks;
    struct s_data_const *next;
} t_const;

typedef struct s_big_data {
    struct t_const *data;
    char **name_all;
    char **file;
    int *flags;
    char **argv_dir;
    char **argv_file;
    char **argv;
    bool isattyflag;
    int max_len_name;
    int num_name;
    int flag_n;
    int colums;
    int size;
    int size_all;
    int width;
    int argc;
    int flag;
} t_data;

void mx_get_flag_l(t_const *cnst);

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
void mx_get_time(struct stat st, t_const *cnst);
void mx_read_link(t_const *cnst);

void mx_print_to_file(char **file);
void mx_check_control_char(char ***str);
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
