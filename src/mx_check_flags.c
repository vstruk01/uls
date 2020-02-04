#include "uls.h"

void mx_check_flags(char *s, t_data *app) {
    mx_basic_flags(s, app);
    mx_flags_for_sort(s, app);
    mx_other_flags(s, app);
    free(s);
}

