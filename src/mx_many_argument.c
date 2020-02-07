#include "uls.h"

static t_const *get_file(t_const *cnst, char *str) {
    if (cnst->name == NULL) {
        cnst->next = NULL;
        cnst->name = str;
    }
    else {
        cnst->next = malloc(sizeof (t_const));
        cnst->next->name = str;
        cnst = cnst->next;
        cnst->next = NULL;
    }
    return cnst;
}

static t_dir *get_dir(t_dir *dir, char *str) {
    if (dir->name == NULL) {
        dir->next = NULL;
        dir->name = str;
    }
    else {
        dir->next = malloc(sizeof (t_dir));
        dir->next->name = str;
        dir = dir->next;
        dir->next = NULL;
    }
    return dir;
}

static int cycle_link(DIR *dir, t_data *data, int i) {
    struct stat st;
    struct stat link;

    lstat(data->dir_arr[i], &link);
    if (S_IFLNK != (S_IFMT & link.st_mode))
        return 1;
    stat(data->dir_arr[i], &st);
    if (mx_last_char(data->dir_arr[i]))
        data->dir = get_dir(data->dir, data->dir_arr[i]);
    else if (mx_flag_link(data))
        data->cnst = get_file(data->cnst, data->dir_arr[i]);
    else if (S_IFDIR != (S_IFMT & st.st_mode))
        data->cnst = get_file(data->cnst, data->dir_arr[i]);
    else if (S_IFDIR == (S_IFMT & st.st_mode))
        data->dir = get_dir(data->dir, data->dir_arr[i]);
    if (dir)
        closedir(dir);
    return 0;
}

static void cycle(DIR *dir, t_data *data, int i) {
    if ((!dir && errno == 20))
        data->cnst = get_file(data->cnst, data->dir_arr[i]);
    else if (!dir && errno != 13)
       mx_error_print(data->dir_arr[i], data);
    else if (!dir && errno == 13)
        data->dir = get_dir(data->dir, data->dir_arr[i]);
    else if (dir) {
        data->dir = get_dir(data->dir, data->dir_arr[i]);
        closedir(dir);
    }
}

void mx_many_argument(t_data *data) {
    DIR *dir = NULL;
    t_dir *save_dir = NULL;
    t_const *save = NULL;

    mx_sort_dir_arr(data);
    save = data->cnst;
    save_dir = data->dir;
    for (int i = 0; data->dir_arr[i]; i++) {
        dir = opendir(data->dir_arr[i]);
        if (cycle_link(dir, data, i))
            cycle(dir, data, i);
    }
    data->dir = save_dir;
    data->cnst = save;
    if (save->name != NULL)
        mx_file_argument(save, data);
    mx_sort_dir(save_dir, data);
    if (save_dir->name != NULL)
        mx_dir_argument(save_dir, data);
}
