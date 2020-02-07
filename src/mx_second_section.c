#include "uls.h"




static int return_n(t_files *files) {
    if (files == NULL || 
        (files -> next == NULL && files -> file_name == NULL)) {
        //mx_printstr("\n");
        return 1;
    }   
    return 0;
}





void mx_second_section(t_files *files, char *flags, char *dir) {
    if (return_n(files))
        return;
    files = files -> next;
  
    if (mx_is_in_arr(flags, 'm'))
        mx_flag_m(files, flags);
    else if (mx_is_in_arr(flags, '1'))
        mx_minus_one(files, flags);
    else if(mx_is_in_arr(flags, 'l'))
        mx_flag_l_output(files, dir, flags);
    else
       mx_pure_output(files, flags);
    mx_printstr("\n");
}
