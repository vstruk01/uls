#include "uls.h"

t_files *mx_create_tfiles(char *file_name) {
    t_files *node = malloc(sizeof(t_files));
    char *f_name;
    struct stat stats;

    if (file_name != NULL) {
        stat(file_name, &stats);
        if(mx_link(file_name, stats))
            lstat(file_name, &stats);
        node -> stats = stats;
        node -> type = mx_file_type(file_name, stats);
    }
    f_name = mx_file_name_retriever(file_name);
    if (f_name != NULL) {
        node -> file_name = f_name;
        free(file_name);
    }
    else 
        node -> file_name = file_name;
    node -> next = NULL;
    return node;
}
