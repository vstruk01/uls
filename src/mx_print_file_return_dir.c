#include "uls.h"

static t_data *get_data(t_data *data, char **file, int size);
static void print(char **file, t_data *data, int size);
static void get_argv(int *size, t_data *data, char ***argv_dir,
char ***argv_file);

int mx_print_file_return_dir(t_data *data, char ***argv_dir) {
    DIR *dir = NULL;
    int tmp[2];
    char **argv_file = NULL;

    tmp[0] = 0;
    tmp[1] = 0;
    for (int i = 1; i < data->argc; i++) {
        dir = opendir((data->argv)[i]);
        if (!dir && errno == 20)
            tmp[0]++;
        else if (dir) {
            closedir(dir);
            tmp[1]++;
        }
    }
    (*argv_dir) = malloc(sizeof(char *) * tmp[1] + 1);
    argv_file = malloc(sizeof(char *) * tmp[0] + 1);
    get_argv(tmp, data, argv_dir, &argv_file);
        if (tmp[0] > 0)
            print(argv_file, data, tmp[0]);
    free(argv_file);
    return tmp[1];
}

static void print(char **file, t_data *data, int size) {
    char **tmp = NULL;
    char **result = NULL;

    data = get_data(data, file, size);
    mx_sort_file(&file, size);
    tmp = malloc(sizeof(char *) * data->size_all + 1);
    result = malloc(sizeof(char *) * data->size_all + 1);
    for (int i = 0; i <= data->size_all; i++) {
        tmp[i] = NULL;
        result[i] = NULL;
    }
    for (int i = 0; file[i] != NULL; i++)
        tmp[i] = file[i];
    result = mx_get_result(tmp, result, data);
    mx_print_file(result, data);
    free(tmp);
    free(result);
    printf("\n");
}

static t_data *get_data(t_data *data, char **file, int size) {
    for (int i = 0; file[i] != NULL; i++)
        if (data->num < mx_strlen(file[i]))
            data->num = mx_strlen(file[i]);
    data->num = data->num + (8 - (data->num % 8));
    data->size = size;
    data->width = data->colums / data->num;
    data->size_all = mx_size_a(data);
    return data;
}

static void get_argv(int *size, t_data *data, char ***argv_dir,
char ***argv_file) {
    int number_dir = 0;
    int number = 0;
    DIR *dir = NULL;

    (*argv_dir)[size[1]] = NULL;
    (*argv_file)[size[0]] = NULL;
    for (int i = 1; i <= data->argc; i++) {
        dir = opendir((data->argv)[i]);
        if (!dir && errno == 20) {
            (*argv_file)[number] = (data->argv)[i];
            number++;
        }
        else if (dir) {
            (*argv_dir)[number_dir] = (data->argv)[i];
            number_dir++;
            closedir(dir);
        }
    }
}
