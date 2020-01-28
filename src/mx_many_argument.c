#include "uls.h"

// static void free_char(t_const *cnst);
// static void free_all(t_const *cnst);
static void first(t_data *data);
static t_const *get_file(t_const *cnst, char *str);
static t_dir *get_dir(t_dir *dir, char *str);
static void cycle(DIR *dir, t_data *data, int i);

void mx_many_argument(t_data *data) {
    DIR *dir = NULL;
    t_dir *save_dir = NULL;
    t_const *save = NULL;

    first(data);
    save = data->cnst;
    save_dir = data->dir;
    for (int i = 0; data->dir_arr[i]; i++) {
        dir = opendir(data->dir_arr[i]);
        cycle(dir, data, i);
    }
    if (save->name != NULL)
        mx_file_argument(save, data);
    if (save_dir->name != NULL)
        mx_dir_argument(save_dir, data);
    // while (data->cnst != NULL) {
        // mx_get_flag_l(data->cnst, data);
        // data->size++;
        // data->cnst = data->cnst->next;
    // }
    // while (save_dir != NULL) {
        // printf("dir -> %s\n", save_dir->name);
        // save_dir = save_dir->next;
    // }
    // data->cnst = save;
    // data->flag_total = 0;
    // if (save->name != NULL)
        // mx_print_l(save, data);
}

static void cycle(DIR *dir, t_data *data, int i) {
    struct stat st;

    if (!dir && errno == 20)
        data->cnst = get_file(data->cnst, data->dir_arr[i]);
    else if (!dir && errno != 13)
        mx_error_print(data->dir_arr[i], data);
    else if (dir) {
        lstat(data->dir_arr[i], &st);
        if (S_IFLNK == ( S_IFMT & st.st_mode)) {
            if ((data->flags[3] || data->flags[5] || data->flags[4] 
                || data->flags[7]) && !mx_last_char(data->dir_arr[i])) {
                data->cnst = get_file(data->cnst, data->dir_arr[i]);
            }
            else
                data->dir = get_dir(data->dir, data->dir_arr[i]);
        }
        else
            data->dir = get_dir(data->dir, data->dir_arr[i]);
        closedir(dir);
    }
}

static void first(t_data *data) {
    int counter = 0;
    
    data->cnst = malloc(sizeof(t_const));
    data->dir = malloc(sizeof(t_dir));
    data->dir->name = NULL;
    data->cnst->name = NULL;
    data->dir->next = NULL;
    data->cnst->next = NULL;
    for (; data->dir_arr[counter]; counter++);
    mx_sort_file(data->dir_arr, counter);
}

static t_const *get_file(t_const *cnst, char *str) {
    if (cnst->name == NULL) {
        cnst->next = NULL;
        cnst->name = str;
    }
    else {
        cnst->next = malloc(sizeof(t_const));
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
        dir->next = malloc(sizeof(t_dir));
        dir->next->name = str;
        dir = dir->next;
        dir->next = NULL;
    }
    return dir;
}
// static void free_all(t_const *cnst) {
//     t_const *tmp = cnst->next;

//     while (tmp != NULL) {
//         free(cnst->ful_n)
//         free(cnst->stracl)
//         free(cnst->name)
//         free(cnst->name_c)
//         free(cnst->strrwx)
//         free(cnst->strtime)
//         free(cnst->strlink)
//         free_char(cnst);
//         free(cnst)
//         cnst = tmp;
//         tmp = tmp->next;
//     }
// }

// static void free_char(t_const *cnst) {
//     free(cnst->strgid)
//     free(cnst->struid)
//     free(cnst->strmaj)
//     free(cnst->strmin)
//     free(cnst->strlinkcount)
//     free(cnst->strbytes)
//     free(cnst->strblocks)
//     free(cnst->strino)
// }
