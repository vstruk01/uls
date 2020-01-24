#include "uls.h"

int main(int argc, char **argv) {
    t_data *data = malloc(sizeof(t_data));
    data->dir_arr = NULL;
    data->path = NULL;
    mx_read_flags(argv, argc, data);
    if (!data->dir_arr) {
        if (mx_read_dir(".", data)) {
            if (data->flags[4] || data->flags[5])
                mx_print_l(data->cnst, data);
            else {
                if (data->flags[8] && data->size > 1)
                    mx_printstr_update("total ",
                    data->strtotal, "\n", NULL, NULL);
                mx_print_file(data);
            }
        }
    }
    else {
        data->path = data->dir_arr[0];
        if (mx_read_dir(data->dir_arr[0], data)) {
            if (data->flags[4] || data->flags[5])
                mx_print_l(data->cnst, data);
            else {
                if (data->flags[8] && data->size > 1)
                    mx_printstr_update("total ",
                    data->strtotal, "\n", NULL, NULL);
                mx_print_file(data);
            }
        }
    }
    // system("leaks -q uls");
    exit(0);
    mx_print_file_return_dir(data);
    for (int i = 0; i < argc; i++) {
        free(data->file);
        data->file = NULL;
        mx_read_dir(argv[i], data);
        if (argc > 2 && data->file != NULL) {
            if (data->flag_n == 1)
                printf("\n");    
            printf("%s:\n", argv[i]);
            data->flag_n = 1;
        }
        if (errno && data->file == NULL && argv[i] != NULL 
            && errno != 2 && errno != 20) {
            if (argc > 2) 
                printf("\n%s:\n", argv[i]);
            printf("uls: %s: %s\n", argv[i], (strerror(errno)));
        }
        else if (data->file != NULL)
            mx_print_file(data);
        for (int i = 0; i < data->size_all && data->file != NULL; i++)
            if ((data->file)[i] != NULL)    
                free((data->file)[i]);
        free(data->file);
        data->file = NULL;
    }
    system("leaks -q uls");
    if (errno)
        return 1;
    // printf("\n");
}











