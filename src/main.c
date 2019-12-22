#include "uls.h"

int main(int argc, char **argv) {
    // time_t time;
    // struct stat st;
// 
    // argc++;
    // stat(argv[1], &st);
    // time = st.st_atime;
    // char *str = ctime(&time);
    // printf("%s", str);
    // exit(0);
    t_data *data = malloc(sizeof(t_data));
    char **argv_dir = NULL;
    int i = 0;
    char **file = NULL;


    //data->flags = malloc(sizeof(int) * 2);
    int flags[2];
    flags[0] = 0;
    flags[1] = 1;
    data->argv = argv;
    data->argc = argc;
    argv++;
    mx_sort_file(&argv, argc - 1);
    data->colums = mx_columns();
    if (argc == 1) {
        file = mx_read_dir(".", flags, data);
        mx_print_file(file, data);
    }
    else {
        i = mx_print_file_return_dir(data, &argv_dir); // -> кілкість переданих аргуменентів
        for (int j = 0; j < i; j++) {
            file = mx_read_dir(argv_dir[j], flags, data);
            if (i != 1)
                printf("%s:\n", argv_dir[j]);
            mx_print_file(file, data);
            if ((j + 1) < i)
                printf("\n");
            for (int i = 0; i < data->size_all; i++)
                if (file[i] != NULL)    
                    free(file[i]);
            free(file);
            file = NULL;
        }
    }
        system("leaks -q uls");
}
