#include "uls.h"


int mx_file_exists(char *file) {
    DIR *dir = opendir(file);
    if (errno == 2) {
        errno = 0;
        free(dir);
        return 0;
    }
    else if (errno == 0) {
        closedir(dir);
    }
    else {
        free(dir);
    }

    errno = 0;
    return 1;
}


