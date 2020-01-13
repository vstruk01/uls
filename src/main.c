#include "uls.h"

int main(int argc, char **argv) {
    struct stat st;
    t_const *cnst = malloc(sizeof(t_const));
    t_data *data = malloc(sizeof(t_data));

    if (argc > 1) {
        cnst->dirname = argv[1];
        mx_read_link(argv[1], cnst);
        lstat(argv[1], &st);
    }
    else {
        cnst->dirname = ".";
        mx_read_link(".", cnst);
        lstat(".", &st);
    }
    mx_get_flag_l(st, cnst);
    exit(0);
    data->flags = malloc(sizeof(int) * 5);
    data->flag_n = 0;
    data->flags[0] = 1; // -a
    data->flags[1] = 0; // -A
    data->flags[2] = 0; // -1
    data->flags[3] = 0; // -C uls
    data->flags[4] = 0; // -l
    data->argv = argv;
    data->argc = argc;
    data->colums = mx_columns();
    argv++;
    mx_sort_file(argv, argc - 1);
    if (argc == 1) {
        data->file = mx_read_dir(".", data);
        mx_print_file(data->file, data);
        if (errno)
            return 1;
    }
    mx_print_file_return_dir(data);
    for (int i = 0; i < argc; i++) {
        free(data->file);
        data->file = NULL;
        data->file = mx_read_dir(argv[i], data);
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
            mx_print_file(data->file, data);
        for (int i = 0; i < data->size_all && data->file != NULL; i++)
            if ((data->file)[i] != NULL)    
                free((data->file)[i]);
        free(data->file);
        data->file = NULL;
    }
    if (errno)
        return 1;
    // printf("\n");
}











