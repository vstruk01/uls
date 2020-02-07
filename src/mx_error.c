#include "uls.h"

static int bad_descriptor(char *dir_name) {
    
    errno = 0;
    DIR *dir_opn = opendir(dir_name);

    if (errno == 9) {
        errno = 0;
        free(dir_opn);
        return 1;
    }
    if (errno == 0)
        closedir(dir_opn);
    else
        free(dir_opn);

    errno = 0;
    return 0;
}

static int all_errors(char *dir_name) {
    errno = 0;
    DIR *dir = opendir(dir_name);

    if (errno == 0)
        closedir(dir);
    else
        free(dir);
    if (errno != 0 && errno != 20 && errno != 2) 
        return 1;
    return 0;
}


int mx_error(char *dir_name) {

    if (mx_permission_denied(dir_name)) {
        return 1;
    }
    else if (mx_file_exists(dir_name) == 0)
        return 1;
    else if (bad_descriptor(dir_name))
        return 1;
    else if (all_errors(dir_name))
        return 1; 

    return 0;
}


