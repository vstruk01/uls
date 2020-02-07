#include "uls.h"



static int get_std_width() {
    struct winsize w;
    int width;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    width = w.ws_col;
    return width;
}


static int long_f(t_files *list) {
    int longest_filename = 0;
    t_files* tmp = list;

    while (tmp) {
        if(tmp->file_name != NULL) {
            if(mx_strlen(tmp->file_name) > longest_filename)
                longest_filename = mx_strlen(tmp->file_name);
        }
        tmp = tmp -> next;
    }
    return longest_filename;
}



static int cols_count(int width ,t_files *list) {
    int longest = long_f(list);
    int cols = width / ((8 - (longest % 8)) + longest);
    int rest = mx_rest(list, cols);
    while (rest < 0) {
        cols--;
        rest = mx_rest(list, cols);
    }
    if(rest <= 0 && mx_count_list(list) > cols)
        cols--;
    if(cols == 2 && mx_count_list(list) == 6)
        cols++;
    if(cols == 0)
        return 1;
    return cols;
}



void mx_pure_output(t_files *list, char *flags) {
	int cols = cols_count(get_std_width(), list);;
    int rest = mx_rest(list, cols);
    char *arr[mx_count_list(list)];

    if (mx_is_in_arr(flags, 'p'))
        mx_flag_p_for_pureoutput(list);
    mx_sort_output(mx_count_list(list), list, cols, arr);


    for(int i = 0; i < mx_count_list(list); i++) {
        if(arr[i] != NULL) {
            if(cols == 0) {
                mx_printstr("\n");
                rest--;
                cols = cols_count(get_std_width(), list);
                if(rest <= 0)
                    cols = cols_count(get_std_width(), list) - 1;
            }
            cols--;
            mx_super_print(list, i, arr);
        }
    }
}
