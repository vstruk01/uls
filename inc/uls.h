#ifndef ULS_H
#define ULS_H

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

typedef struct s_file {
    char *d_name;
    struct s_file *next;
} t_file;

typedef struct s_data_const {
    // time = st.st_mtime;
    // int ino = st.st_ino;
    // int size = st.st_size;
    // int link =  st.st_nlink;
    // int rdev = st.st_rdev;
    // int gid = st.st_gid;
    // int uid = st.st_uid;
    // int bloks = st.st_blocks;
    time_t time;
    char *strrwx;
    char *strtime;
    int ino;
    int size_bytes;
    int link;
    int rdev;
    int gid;
    int uid;
    int bloks;
    struct s_data_const *next;
} t_const

typedef struct s_big_data {
    char **file;
    int *flags;
    char **argv_dir;
    char **argv_file;
    char **d_name;
    int num;
    int flag_n;
    int colums;
    int size;
    int size_all;
    int width;
    int argc;
    int flag;
    char **argv;
} t_data;

void mx_get_size_bytes(struct stat st, t_data *data);
void mx_get_ino(struct stat st, t_data *data);
void mx_get_time(struct stat st, t_data *data);

char *mx_read_link(char *dirname);
void mx_print_to_file(char **file);
void mx_check_control_char(char ***str);
void mx_sort_file(char **str, int size);
int mx_size_a(t_data *data);
char **mx_get_result(char **file, t_data *data);
void mx_print_file_return_dir(t_data *data);
int mx_head_size(t_file *head);
int mx_columns();
void mx_print_file(char **file, t_data *data);
int mx_num_file(t_file *head);
char **mx_read_dir(char *dirname, t_data *data);

#endif 
