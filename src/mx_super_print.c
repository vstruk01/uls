#include "uls.h"


static void print(char* string, int space_size) {
	for(int i = 1; i < space_size - mx_strlen(string); i++)
        mx_printstr(" ");
}

static int long_n(t_files *list) {
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

void mx_super_print(t_files *list, int i, char *arr[mx_count_list(list)]) {
	mx_printstr(arr[i]);
    print(arr[i], long_n(list) + (8 - (long_n(list) % 8)) + 1);
}
