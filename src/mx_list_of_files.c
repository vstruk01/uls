#include "uls.h"



static char *slash_adder(char *dir, char *d_name) {
    char *file_path;

    if (dir[mx_strlen(dir) - 1] != '/') {
        file_path = mx_three_join(dir, "/", d_name);
    }
    else {
        file_path = mx_strjoin(dir, d_name);
    }
    return file_path;
}

static int mx_is_to_hide(char *file_name, char *flags) {
    if (mx_is_in_arr(flags, 'a') == 0 && mx_is_in_arr(flags, 'A') == 0) {
      if (mx_strcmp(file_name, ".") == 0 
            || mx_strcmp(file_name, "..") == 0
            || file_name[0] == '.')
            return 1;
    }
    else if (mx_is_in_arr(flags, 'A') == 1)
        if  (mx_strcmp(file_name, ".") == 0 
            || mx_strcmp(file_name, "..") == 0)
            return 1;
    return 0;
}


static int num_of_files_f(char *dir_name, char *flags) {
    DIR *dir_opn = opendir(dir_name);
    struct dirent *entry;
    int num = 0;

    if (mx_permission_denied(dir_name))
        return 0;
    while ((entry = readdir(dir_opn))!= NULL)
       if (mx_is_to_hide(entry -> d_name, flags) == 0) 
            num++;
    closedir(dir_opn);
    return num;
}



char **mx_list_of_files(char *dir_name, char *flags, char* file_path) {
    int num_of_files= num_of_files_f(dir_name, flags);
    if (num_of_files == 0)
        return NULL;
    char **list_of_files = mx_new_strarr(num_of_files);
    DIR *dir_opn = opendir(dir_name);
    struct dirent *entry;
    int index = 0;

    if (mx_error(dir_name))
        return NULL;
    while ((entry = readdir(dir_opn)) != NULL) {
        file_path = slash_adder(dir_name, entry -> d_name);
        if (mx_is_to_hide(entry -> d_name, flags) == 0) {    
            list_of_files[index] = mx_string_copy(file_path);
            index++;
        }
        free(file_path);
    }
    closedir(dir_opn);
    return list_of_files;
}
