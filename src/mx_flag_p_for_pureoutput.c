#include "uls.h"


void mx_flag_p_for_pureoutput(t_files *list) {
    t_files *tmp = list;

    if (tmp) {
        while(tmp) {
            if (tmp -> type == 'd') {
                char *tmp_name = mx_strjoin(tmp -> file_name, "/");
                free(tmp -> file_name);
                tmp -> file_name = tmp_name;
            }
            tmp = tmp -> next;
        }
    }
}
