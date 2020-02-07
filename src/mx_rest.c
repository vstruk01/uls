#include "uls.h"



static int mx_count_files(t_files* list) {
    int count = 0;
    t_files *tmp = list;

    while(tmp) {
        count++;
        tmp = tmp -> next;
    }

    return count;
}


int mx_rest(t_files* list, int cols) {
    int rows = 0;
    int rest = 0;

    if (cols == 0)
        cols += 1;

    if(mx_count_files(list) % cols != 0) {
    
        rows = (mx_count_files(list) / cols) + 1;
        rest = rows - ((rows * cols) - mx_count_files(list));
    }
    if(rows == 1)
        rest = rows;
    if (rows == 0)
        rest = 120;
    return rest;
}
