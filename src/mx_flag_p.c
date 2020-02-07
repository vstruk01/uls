#include "uls.h"


void mx_flag_p(t_files *files, char *flags) {
    
    if (mx_is_in_arr(flags, 'p') && files -> type == 'd')
        mx_printstr("/");
}

