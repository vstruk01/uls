#include "uls.h"

int main(int argc, char **argv) {
    t_data *data = malloc(sizeof(t_data));
    data->flags = malloc(sizeof(int) * 14);
    data->flag_n = 0;
    data->flags[0] = 1; // -a
    data->flags[1] = 0; // -A
    data->flags[2] = 0; // -1
    data->flags[3] = 0; // -C
    data->flags[4] = 0; // -l
    data->flags[5] = 0; // -o
    data->flags[6] = 0; // -T
    data->flags[7] = 0; // -i
    data->flags[8] = 0; // -s
    data->flags[9] = 0; // -f
    data->flags[10] = 0; // -S
    data->flags[11] = 0; // -t
    data->flags[12] = 0; // -r
    data->flags[13] = 0; // -u
    data->argv = argv;
    data->argc = argc;
    mx_sort_file(argv += 1, argc - 1);
    argv--;
    if (argc == 1) {
        data->path = argv[1];
        if (mx_read_dir(".", data)) {
            if (data->flags[4] || data->flags[5])
                mx_print_l(data->cnst, data);
            mx_print_file(data);
        }
    }
    else {
        data->path = argv[1];
        if (mx_read_dir(argv[1], data)) {
            if (data->flags[4] || data->flags[5])
                mx_print_l(data->cnst, data);
            mx_print_file(data);
        }
    }
    system("leaks -q uls");
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











