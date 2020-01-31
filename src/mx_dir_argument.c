#include "uls.h"

static void get_int(t_data *data);
static t_data *get_data(t_data *data);
static void read_dir(t_data *data, t_dir *dir);

void mx_dir_argument(t_dir *dir, t_data *data) {
    int flag = 1;

    if (data->cnst->name != NULL)
        mx_printstr("\n");
    if (dir->next == NULL && !(data->errors == 2 || data->cnst->name != NULL))
        flag = 0;
    data = get_data(data);
    while (dir != NULL) {
        data->path = dir->name;
        if (flag)
            mx_printstr_update(dir->name, ":", "\n", NULL, NULL);
        read_dir(data, dir);
        flag = 1;
        if (dir->next != NULL) {
            mx_printstr("\n");
        }
        dir = dir->next;
        data = get_data(data);
    }
}

static void read_dir(t_data *data, t_dir *dir) {
    if (mx_read_dir(dir->name, data)) {
        if (data->flags[4] || data->flags[5] || data->flags[3]) {
            mx_print_l(data->cnst, data);
            data->flag_total = 1;
        }
        else {
            if (data->flags[8]) {
                mx_printstr_update("total ",
                data->strtotal, "\n", NULL, NULL);
            }
            mx_print_file(data);
        }
    }
}

static t_data *get_data(t_data *data) {
    data->next = malloc(sizeof(t_data));
    data->next->flags = data->flags;
    data = data->next;
    data->next = NULL;
    get_int(data);
    return data;
}

static void get_int(t_data *data) {
    data->max_len_bytes = 0;
    data->max_len_link = 0;
    data->max_len_min = 0;
    data->max_len_maj = 0;
    data->max_len_gid = 0;
    data->max_len_ino = 0;
    data->max_len_uid = 0;
    data->max_len_blocks = 0;
    data->size = 0;
    data->acl = 0;
    data->total = 0;
    data->link = 0;
    data->isattyflag = 0;
    data->colums = 0;
    data->flag_total = 0;
    data->size_all = 0;
    data->width = 0;
    data->flag_minmaj = 0;
}

