#include "uls.h"

static void get_strstr(t_const *data_l, t_data *data);
static t_const *get_name(t_const *data_l, struct dirent *entry);
static void flag_a_A_free(t_const *data_l, DIR *dir, int *flags);

void mx_read_dir(char *dirname, t_data *data) {
    DIR *dir = opendir(dirname);
    t_const *data_l = malloc(sizeof(t_const));
    t_const *save = data_l;

    if (!dir)
        return;
    flag_a_A_free(data_l, dir, data->flags);
    data_l = save->next;
    free(save);
    closedir(dir);
    mx_head_size(data_l, data);
    mx_num_file(data_l, data);
    get_strstr(data_l, data);
}

static void flag_a_A_free(t_const *data_l, DIR *dir, int *flags) {
    struct dirent *entry = NULL;

    if (flags[0] == 1)
        while ((entry = readdir(dir)) != NULL)
            data_l = get_name(data_l, entry);
    else if (flags[1] == 1) {
        while ((entry = readdir(dir)) != NULL)
            if (strcmp(entry->d_name, ".") != 0 
                && strcmp(entry->d_name, "..") != 0) {
                data_l = get_name(data_l, entry);
            }
    }
    else
        while ((entry = readdir(dir)) != NULL)
            if (entry->d_name[0] != '.')
                data_l = get_name(data_l, entry);
}

static void get_strstr(t_const *data_l, t_data *data) {
    char **file = NULL;

    file = malloc(sizeof(char *) * data->size_all);
    for (int i = 0; i < data->size_all; i++)
        file[i] = NULL;
    for (int i = 0; data_l != NULL; i++) { 
        file[i] = data_l->name;
        data_l = data_l->next;
    }
    mx_sort_file(file, data->size);
    if (isatty(1) == 0) {
        data->name_all = file;
        data->isattyflag = 1;
    }
    data->name_all = mx_get_result(file, data);
    free(file);
}

static t_const *get_name(t_const *data_l, struct dirent *entry) {
    data_l->next = malloc(sizeof(t_const));
    data_l->next->name = mx_strdup(entry->d_name);
    mx_get_flag_l(data_l->next);
    data_l = data_l->next;
    data_l->next = NULL;
    return data_l;
}
