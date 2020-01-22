#include "uls.h"

static void get_strstr(t_const *data_l, t_data *data);
static t_const *get_name(t_const *data_l, struct dirent *entry, t_data *data);
static void flag_a_A(t_const *data_l, DIR *dir, int *flags, t_data *data);

int mx_read_dir(char *dirname, t_data *data) {
    // struct stat st;
    DIR *dir = opendir(dirname);
    t_const *data_l = malloc(sizeof(t_const));
    t_const *save = data_l;

    // lstat(dirname, &st);
    // data_l->name = dirname;
    // data->size = 1;
    // mx_get_data(data, data_l);
    // if (mx_islink(data_l)) {
        // mx_head_size(data_l, data);
        // mx_num_file(data_l, data);
        // closedir(dir);
        // data->cnst = data_l;
        // return;
    // }
    if (!dir) {
        if (errno == 13 || errno == 9)
            printf("uls: %s: %s\n", dirname, strerror(errno));
        free(save);
        return 0;
    }
    flag_a_A(data_l, dir, data->flags, data);
    data_l = save->next;
    free(save);
    closedir(dir);
    mx_head_size(data_l, data);
    mx_num_file(data_l, data);
    data->cnst = data_l;
    mx_sort_all(data, data_l);
    mx_get_data(data, data_l);
    get_strstr(data_l, data);
    return 1;
}

static void flag_a_A(t_const *data_l, DIR *dir, int *flags, t_data *data) {
    struct dirent *entry = NULL;

    if (flags[0] == 1 || flags[9] == 1)
        while ((entry = readdir(dir)) != NULL)
            data_l = get_name(data_l, entry, data);
    else if (flags[1] == 1) {
        while ((entry = readdir(dir)) != NULL)
            if (strcmp(entry->d_name, ".") != 0 
                && strcmp(entry->d_name, "..") != 0) {
                data_l = get_name(data_l, entry, data);
            }
    }
    else
        while ((entry = readdir(dir)) != NULL)
            if (entry->d_name[0] != '.')
                data_l = get_name(data_l, entry, data);
}

static void get_strstr(t_const *data_l, t_data *data) {
    char **file = NULL;

    file = malloc(sizeof(char *) * (data->size_all + 1));
    for (int i = 0; i <= data->size_all; i++)
        file[i] = NULL;
    for (int i = 0; data_l != NULL; i++) { 
        file[i] = data_l->name;
        data_l = data_l->next;
    }
    if (isatty(1) == 0 || data->flags[2]) {
        data->name_all = file;
        data->isattyflag = 1;
        return;
    }
    data->name_all = mx_get_result(file, data);
    free(file);
}

static t_const *get_name(t_const *data_l, struct dirent *entry, t_data *data) {
    data_l->next = malloc(sizeof(t_const));
    data_l->next->name = mx_strdup(entry->d_name);
    data->size_list += 1;
    data_l = data_l->next;
    data_l->next = NULL;
    return data_l;
}
