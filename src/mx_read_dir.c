#include "uls.h"

static void get_strstr(t_file *name, t_data *data, char ***result);
static t_file *get_name(t_file *name, struct dirent *entry);
static void flag_a_A_free(t_file *name, DIR *dir, int *flags);

char **mx_read_dir(char *dirname, int *flags, t_data *data) {
    DIR *dir = opendir(dirname);
    t_file *name = malloc(sizeof(t_file));
    t_file *savename = name;
    char **result = NULL;

    name->next = NULL;
    flag_a_A_free(name, dir, flags);
    while (savename->next->next != NULL)
        savename = savename->next;
    free(savename->next);
    savename->next = NULL;
    closedir(dir);
    data->num = mx_num_file(name);
    data->size = mx_head_size(name);
    data->width = data->colums / data->num;
    get_strstr(name, data, &result);
    return result;
}

static void flag_a_A_free(t_file *name, DIR *dir, int *flags) {
    struct dirent *entry = NULL;

    if (flags[0] == 1)
        while ((entry = readdir(dir)) != NULL)
            name = get_name(name, entry);
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

static void get_strstr(t_file *name, t_data *data, char ***result) {
    data->size_all = mx_size_a(data);
    char **file = malloc(sizeof(char *) * data->size_all);
    t_file *tmp = name;

    *result = malloc(sizeof(char *) * data->size_all);
    for (int i = 0; i < data->size_all; i++) {
        file[i] = NULL;
        (*result)[i] = NULL;
    }
    for (int i = 0; name != NULL; i++) { 
        tmp = name;
        file[i] = name->d_name;
        name = name->next;
        free(tmp);
    }
    mx_sort_file(&file, data->size);
    (*result) = mx_get_result(file, (*result), data);
    free(file);
}

static t_file *get_name(t_file *name, struct dirent *entry) {
    name->d_name = mx_strdup(entry->d_name); 
    name->next = malloc(sizeof(t_file));
    name = name->next;
    name->next = NULL;
    return name;
}
