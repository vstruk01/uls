#include "uls.h"

static int check_m(char s, t_data *app) {
    if (s == 'm') {
        app->flags[14] = 1;
        app->flags[5] = 0;
        app->flags[3] = 0;
        return 1;
    }
    return 0;
}

static int is_flag_1(char cont, t_data *app) {
    if (cont == '1') {
        app->flags[2] = 1;
        app->flags[3] = 0;
        app->flags[5] = 0;
        return 1;
    }
    return 0;
}

static int is_flag_c(char *cont, t_data *app, int i) {
    if (cont[i] == 'C') {
        app->flags[17] = 1;
        return 1;
    }
    return 0;
}

static void flags_include_basic(char *cont, t_data *app) {
    if (mx_get_char_index(cont, 'T') >= 0)
        app->flags[6] = 1;
    if (mx_get_char_index(cont, 'g') >= 0)
        app->flags[3] = 1;
    if (mx_get_char_index(cont, 'o') >= 0)
        app->flags[5] = 1;
    if (mx_get_char_index(cont, 'O') >= 0)
        app->flags[21] = 1;
    for (int i = mx_strlen(cont) - 1; i >= 0; i--) {
        if (cont[i] == 'c') {
            app->flags[22] = 1;
            break;
        }
        else if (cont[i] == 'u') {
            app->flags[13] = 1;
            break;
        }
    }
    if (mx_get_char_index(cont, '@') >= 0)
        app->flags[25] = 1;
}

void mx_basic_flags(char *cont, t_data *app) {
    flags_include_basic(cont, app);
    for (int i = mx_strlen(cont) - 1; i >= 0; i--) {
        if (is_flag_1(cont[i], app) == 1)
            break;
        if (is_flag_c(cont, app, i) == 1)
            break;
        if (cont[i] == 'x' && (app->flags[24] += 1) > 0)
            break;
        if (check_m(cont[i], app))
            break;
        if (cont[i] == 'o' && (app->flags[5] += 1) > 0)
            break;
        if (cont[i] == 'g' && (app->flags[3] += 1) > 0)
            break;
        if (cont[i] == 'l') {
            app->flags[4] = 1;
            break;
        }
    }
}

