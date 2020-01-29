#include "uls.h"

void mx_error_print(char *str, t_data *data) {
    mx_print_error("uls: ");
    mx_print_error(str);
    mx_print_error(": ");
    mx_print_error(strerror(errno));
    mx_print_error("\n");
    data->errors = 2;
}
