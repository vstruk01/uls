#include "uls.h"

static char **get_strstr(t_file *name, t_data *data);
static t_file *get_name(t_file *name, struct dirent *entry);
static void flag_a_A_free(t_file *name, DIR *dir, int *flags);

char **mx_read_dir(char *dirname, t_data *data) {
    DIR *dir = opendir(dirname);
    t_file *name = malloc(sizeof(t_file));
    t_file *savename = name;
    char **result = NULL;

    if (!dir)
        return NULL;
    name->next = NULL;
    name->d_name = NULL;
    flag_a_A_free(name, dir, data->flags);
    while (savename->next != NULL && savename->next->next != NULL)
        savename = savename->next;
    free(savename->next);
    savename->next = NULL;
    closedir(dir);
    data->num = mx_num_file(name);
    data->size = mx_head_size(name);
    data->width = data->colums / data->num;
    result = get_strstr(name, data);
    return result;
}

static void flag_a_A_free(t_file *name, DIR *dir, int *flags) {
    struct dirent *entry = NULL;

    if (flags[0] == 1)
        while ((entry = readdir(dir)) != NULL) {
            name = get_name(name, entry);
        }
    else if (flags[1] == 1) {
        while ((entry = readdir(dir)) != NULL)
            if (strcmp(entry->d_name, ".") != 0 
                && strcmp(entry->d_name, "..") != 0) {
                name = get_name(name, entry);
            }
    }
    else 
        while ((entry = readdir(dir)) != NULL)
            if (entry->d_name[0] != '.')
                name = get_name(name, entry);
}

static char **get_strstr(t_file *name, t_data *data) {
    char **file = NULL;
    char **result = NULL;
    t_file *tmp = name;

    data->size_all = mx_size_a(data);
    file = malloc(sizeof(char *) * data->size_all);
    for (int i = 0; i < data->size_all; i++)
        file[i] = NULL;
    for (int i = 0; name != NULL; i++) { 
        tmp = name;
        file[i] = name->d_name;
        name = name->next;
        free(tmp);
    }
    mx_sort_file(file, data->size);
    if (isatty(1) == 0)
        return file;
    result = mx_get_result(file, data);
    free(file);
    return result;
}

static t_file *get_name(t_file *name, struct dirent *entry) {
    name->d_name = mx_strdup(entry->d_name); 
    name->next = malloc(sizeof(t_file));
    name = name->next;
    name->next = NULL;
    return name;
}
