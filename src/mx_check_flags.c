#include "uls.h"

void mx_check_flags(char *s, t_data *app) {
    int len = mx_strlen(s);

    mx_basic_flags(s, app, len);
    mx_flags_for_sort(s, app);
    mx_other_flags(s, app);
    free(s);
}

