#include "uls.h"

static void check_arr_flags(t_data *app, char *s) {
    int i;

    app->str = MX_FLAGS;
    for (i = 0; i < mx_strlen(s); i++)
        if (mx_get_char_index(app->str, s[i]) < 0)
            mx_printerr(INVALID_FLAGS, s[i]);
}

void mx_flags_into_arr(char *s, t_data *app) {
    int size = mx_strlen(MX_FLAGS) + 1;

    app->flags = malloc(size * sizeof (int));
    for (int i = 0; i < size; i++) {
        app->flags[i] = 0;
    }
    mx_check_flags(s, app);
    check_arr_flags(app, s);
}
