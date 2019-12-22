#include "uls.h"

int mx_num_file(t_file *head) {
    int num = 0;

    while (head != NULL) {
        if (num < mx_strlen(head->d_name))
            num = mx_strlen(head->d_name);
        head = head->next;
    }
    num = num + ( 8 - (num % 8));
    return num;
}
