#include "uls.h"

// static char *resolution(struct stat st);

int main(int argc, char **argv) {
    // time_t time;
    // struct stat st;

    // argc++;
    // stat(argv[1], &st);
    // time = st.st_atime;
    // char *str = ctime(&time);
    // printf("%s", str);
    // exit(0);
    // if (argc > 1)
    //     stat(argv[1], &st);
    // else 
    //     stat(".", &st);
    // char *str = resolution(st);
    // printf("%s\n", str);
    // free(str);
    t_data *data = malloc(sizeof(t_data));

    data->flags = malloc(sizeof(int) * 5);
    data->flags[0] = 0; // -a
    data->flags[1] = 0; // -A
    data->flags[2] = 1; // -1
    data->flags[3] = 0; // -C uls
    data->flags[4] = 0; // -l
    data->argv = argv;
    data->argc = argc;
    data->colums = mx_columns();
    argv++;
    mx_sort_file(argv, argc - 1);
    if (argc == 1) {
        data->file = mx_read_dir(".", data);
        // printf("%s\n", data->file[0]);m
        mx_print_file(data->file, data);
        return errno;
    }
    mx_print_file_return_dir(data);
    for (int i = 0; i < argc; i++) {
        free(data->file);
        data->file = NULL;
        data->file = mx_read_dir(argv[i], data);
        if (i != 1 || argc > 2 )
            printf("%s:\n", argv[i]);
        if (errno == 13)
            printf("uls: %s: %s\n", argv[i], (strerror(errno)));
        else 
            mx_print_file(data->file, data);
        if (i < argc)
            printf("\n");
        for (int i = 0; i < data->size_all && data->file != NULL; i++)
            if ((data->file)[i] != NULL)    
                free((data->file)[i]);
        free(data->file);
        data->file = NULL;
    }
    system("leaks -q uls");
}

// static char *resolution(struct stat st) {
//     char *rigths = mx_strnew(9);

//     rigths[0] = (S_IRUSR & st.st_mode) ? 'r' : '-';        
//     rigths[1] = (S_IWUSR & st.st_mode) ? 'w' : '-';
//     rigths[2] = (S_IXUSR & st.st_mode) ? 'x' : '-';
//     rigths[3] = (S_IRGRP & st.st_mode) ? 'r' : '-';
//     rigths[4] = (S_IWGRP & st.st_mode) ? 'w' : '-';
//     rigths[5] = (S_IXGRP & st.st_mode) ? 'x' : '-';
//     rigths[6] = (S_IROTH & st.st_mode) ? 'r' : '-';
//     rigths[7] = (S_IWOTH & st.st_mode) ? 'w' : '-';
//     rigths[8] = (S_IXOTH & st.st_mode) ? 'x' : '-';
//      if (S_ISGID & st.st_mode)
//         rigths[5] = rigths[5] == 'x' ? 's' : 'S';
//     if (S_ISUID & st.st_mode)
//         rigths[2] = rigths[2] == 'x' ? 's' : 'S';
//     if (S_ISVTX & st.st_mode)
//         rigths[8] = rigths[8] == 'x' ? 't' : 'T';
//     return rigths;
// }

