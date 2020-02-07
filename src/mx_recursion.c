#include "uls.h"


static void name_printer(char *dir_name, int checker) {
    if (checker != 0) {
        mx_printstr(dir_name);
        mx_printstr(":\n");
    }
}

static void recursion_maker(char *dir_name, char *flags, int checker) {       
    name_printer(dir_name, checker);
    checker++;
    t_files *files = mx_files_list_maker(dir_name, flags);
    mx_second_section(files, flags, dir_name);    
    mx_tfiles_freesher(files);
    char **list_of_dirs = mx_list_of_dirs(dir_name);
    if (list_of_dirs != NULL) {
        mx_quicksort_strarr(list_of_dirs, 0, mx_strarr_size(list_of_dirs) - 1);
        for (int i = 0; i < mx_strarr_size(list_of_dirs); ++i) {
            if (mx_error(list_of_dirs[i]))
                continue;
            if (mx_a_checker(list_of_dirs[i], flags) == 1)    
                continue;
            if (list_of_dirs[i] != NULL)
                write(1, "\n", 1);
            recursion_maker(list_of_dirs[i], flags, checker);
        }
        mx_free_strarr(list_of_dirs);
    }
}



void mx_recursion(char **specified_dirs, char *flags) {
    int ch = 0;
    if (mx_strarr_size(specified_dirs) > 1)
        ch++;
    for (int i = 0; i < mx_strarr_size(specified_dirs); ++i) {
        if (mx_error(specified_dirs[i])) 
            continue;
        if (mx_type(specified_dirs[i])  == 'd') 
            recursion_maker(specified_dirs[i], flags, ch);
        else {
            t_files *files = mx_files_list_maker(specified_dirs[i], flags);
            mx_second_section(files, flags, specified_dirs[i]); 
            if (specified_dirs[i + 1] != NULL)
                if (mx_type(specified_dirs[i + 1])  == 'd')
                    write(1, "\n", 1);
            mx_tfiles_freesher(files);
        }
    }
}


















