#include "uls.h"


static int get_std_width() {
    struct winsize w;
    int width;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    width = w.ws_col;
    return width;
}


void mx_flag_m(t_files *files, char *flags) {
    t_files *tmp = files;
    int terminal_width = get_std_width();
    int counter = 0;

    if (tmp -> file_name == NULL)
        tmp = tmp -> next;
    while(tmp) {
        if (counter + mx_strlen(tmp -> file_name) + 2 > terminal_width) {
            write(1, "\n", 1);
            counter = 0;
        }
        mx_printstr(tmp -> file_name);
        mx_flag_p(tmp, flags);
        if (tmp -> next != NULL) 
            mx_printstr(", ");
        counter += mx_strlen(tmp -> file_name) + 2; 
        tmp = tmp -> next;
    }
} 


