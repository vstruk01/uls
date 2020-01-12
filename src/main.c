#include "uls.h"

static char *resolution(struct stat st);

int main(int argc, char **argv) {
    struct stat st;
    char *buf = NULL;
    t_const *cnst = malloc(sizeof(t_const));
    t_data *data = malloc(sizeof(t_data));

    if (argc > 1) {
        buf = mx_read_link(argv[1]);
        lstat(argv[1], &st);
    }
    else {
        buf = mx_read_link(".");
        lstat(".", &st);
    }
    mx_get_time(st, data);
    mx_get_ino(st, data);
    mx_get_size_bytes(st, data);
    mx_get_link(st, data);
    data->link =  st.st_nlink;
    data->rdev = st.st_rdev;
    data->gid = st.st_gid;
    data->uid = st.st_uid;
    data->bloks = st.st_blocks;
    data->strrwx = resolution(st);
    printf ("link -> %s\n", buf);
    printf("gid -> %d\nuid -> %d\n", data->gid, data->uid);
    printf("rdev -> %d\n", data->rdev);
    printf("bloks -> %d\n", data->bloks);
    printf("sizebit -> %d\n", data->size);
    printf("ino -> %d\n", data->ino);
    printf("strtime -> %s", data->strtime);
    printf("link -> %d\n", data->link);
    printf("strrwx -> %s\n", data->strrwx);
    free(data->strrwx);
    exit(0);

    data->flags = malloc(sizeof(int) * 5);
    data->flag_n = 0;
    data->flags[0] = 1; // -ac
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

static char *resolution(struct stat st) {
    char *rigths = mx_strnew(9);

    rigths[0] = (S_IRUSR & st.st_mode) ? 'r' : '-';        
    rigths[1] = (S_IWUSR & st.st_mode) ? 'w' : '-';
    rigths[2] = (S_IXUSR & st.st_mode) ? 'x' : '-';
    rigths[3] = (S_IRGRP & st.st_mode) ? 'r' : '-';
    rigths[4] = (S_IWGRP & st.st_mode) ? 'w' : '-';
    rigths[5] = (S_IXGRP & st.st_mode) ? 'x' : '-';
    rigths[6] = (S_IROTH & st.st_mode) ? 'r' : '-';
    rigths[7] = (S_IWOTH & st.st_mode) ? 'w' : '-';
    rigths[8] = (S_IXOTH & st.st_mode) ? 'x' : '-';
     if (S_ISGID & st.st_mode)
        rigths[5] = rigths[5] == 'x' ? 's' : 'S';
    if (S_ISUID & st.st_mode)
        rigths[2] = rigths[2] == 'x' ? 's' : 'S';
    if (S_ISVTX & st.st_mode)
        rigths[8] = rigths[8] == 'x' ? 't' : 'T';
    return rigths;
}











