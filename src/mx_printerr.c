#include "uls.h"

void mx_printerr(t_errors errors, char s) {
    if(errors == INVALID_FLAGS) {
        mx_print_error("uls: illegal option -- ");
        mx_printerr_char(s);
        mx_print_error("\n");
        mx_print_error("usage: uls [");
        mx_print_error(MX_FLAGS);
        mx_print_error("] [file ...]");
    }
    mx_print_error("\n");
    exit(1);
}
