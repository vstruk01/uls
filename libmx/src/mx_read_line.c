#include "libmx.h"

static char *file_to_str(char *buf, int c, int fd) {
    char *result = NULL;
    char *free_tmp = NULL; 

    while (c > 0) {
        if (c == 255) {
            buf[c] = '\0';
            free_tmp = result;
            result = mx_strjoin(free_tmp, buf);
            free(free_tmp);
        }
        else if (c < 255) {
            buf[c] = '\0';
            free_tmp = result;
            result = mx_strjoin(free_tmp, buf);
            free(free_tmp);
        }
        c = read(fd, buf, 255);
    }
    return result; 
}

static char *file(const int fd) {
    char buf[256];
    int c = read(fd, buf, 255);
    char *result = file_to_str(buf, c, fd);

    return result;
}

static char *get_remainder(char *read_strall, int first) {
    int last = mx_strlen(read_strall);
    char *result = mx_strnew(last - first);
    int j = 0;

    for (int i = first; i < last; i++, j++)
        result[j] = read_strall[i];
    return result;
}

static char *get_read_strall(char **remainder, int fd, int buf_size) {
    char *read_strall = NULL;
    char *tmp = NULL;

    buf_size++;
    if (remainder[fd]) {
        tmp = read_strall;
        read_strall = remainder[fd];
        free(tmp);
    }
    else { 
        tmp = read_strall;
        read_strall = file(fd);
        free(tmp);
    }
    return read_strall;
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {    
    static char *remainder[4096];
    char *read_strall = get_read_strall(remainder, fd, buf_size);
    char *tmp = NULL; 
    int get_char = get_char = mx_get_char_index(read_strall, delim);

    if (get_char > -1) {
        tmp = *lineptr;
        *lineptr = mx_strndup(read_strall, get_char);    
        free(tmp);
        tmp = read_strall;
        remainder[fd] = get_remainder(read_strall, get_char + 1);
        free(tmp);
        return mx_strlen(*lineptr);
    }
    else if (get_char < 0) {
        tmp = *lineptr;
        *lineptr = mx_strdup(read_strall);    
        free(tmp);
    }
    return -1;
}
