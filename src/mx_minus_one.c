#include "uls.h"



/*
    Implementation of -1 flag
*/
void mx_minus_one(t_files *files, char *flags) {
    
    t_files *tmp = files;
    while (tmp) {
        if (tmp -> file_name != NULL) {
            mx_printstr(tmp -> file_name);
            mx_flag_p(files, flags);
            if (tmp -> next != NULL)
                mx_printstr("\n");
        }
        tmp = tmp -> next;
    }
}






