#include "uls.h"

t_dirs *mx_create_tdirs(char *dir_name) {
    t_dirs *node = malloc(sizeof(t_dirs));

    node -> dir_name = dir_name;
    node -> next = NULL;
    return node;
}

