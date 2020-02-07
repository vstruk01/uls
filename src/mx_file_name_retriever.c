#include "uls.h"


static int last_slash_finder(char *file_path) {

    int len = mx_strlen(file_path) - 1;

    while (len >= 0) {
        if (file_path[len] == '/') {
            return len;
        }
        len--;
    }
    return -1;
}


char *mx_file_name_retriever(char *file_path) {
    if (file_path == NULL)
        return NULL;
    int last_slash_index = last_slash_finder(file_path);

    if (last_slash_index == -1)
        return NULL;
   
    int x = mx_strlen(file_path) - last_slash_index;
    char *f_name = mx_strnew(x);
    int index = 0;

    while (file_path[last_slash_index + 1]) {
        f_name[index] = file_path[last_slash_index + 1];
        index++;
        last_slash_index++;
    }
    return f_name;  
}










