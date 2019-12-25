#include "uls.h"

static t_data *get_data(t_data *data, int size);
static void print(t_data *data, int size);
static void get_file(int size, t_data *data);

void mx_print_file_return_dir(t_data *data) {
    DIR *dir = NULL;
    int size = 0;
    int number = 0;

    data->file = malloc(sizeof(char *) * data->argc);
    for (int i = 1; i < data->argc; i++) {
        dir = opendir((data->argv)[i]);
        if (!dir && errno == 20) {
            data->file[number++] = data->argv[i];  
            size++;
        }
        else
            closedir(dir);
    }
    data->argv_file = malloc(sizeof(char *) * size + 1);
    get_file(size, data);
    if (size > 0)
        print(data, size);
}

static void print(t_data *data, int size) {
    char **tmp = NULL;
    char **result = NULL;

    data = get_data(data, size);
    mx_sort_file(data->argv_file, size);
    result = mx_get_result(data->argv_file, data);
    for(int i = 0; i < data->size_all; i++)
        printf("%s\n", result[i]);
    exit(0);
    mx_print_file(result, data);
    free(tmp);
    free(result);
    printf("\n");
}

static t_data *get_data(t_data *data, int size) {
    data->num = 0;
    for (int i = 0; i < size; i++)
        if (data->file[i] != NULL && data->num < mx_strlen(data->file[i]))
            data->num = mx_strlen(data->file[i]);
    data->num = data->num + (8 - (data->num % 8));
    data->size = size;
    data->width = data->colums / data->num;
    data->size_all = mx_size_a(data);
    return data;
}

static void get_file(int size, t_data *data) {  
    int number = 0;
    DIR *dir = NULL;

    data->argv_file[size] = NULL;
    for (int i = 1; i < data->argc; i++) {
        dir = opendir(data->argv[i]);
        if (!dir && errno == 20) {
            data->argv_file[number] = data->argv[i];
            number++;
        }
        else
            closedir(dir);
    }
  
}
