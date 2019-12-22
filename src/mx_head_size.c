#include "uls.h"

int mx_head_size(t_file *head) {
    int size = 0;

    for (;head != NULL; size++)
        head = head->next;
    return size;
}
