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



void mx_basic_flags(char *cont, t_data *app) {
    for (int i = mx_strlen(cont) - 1; i >= 0; i--) {
        if (is_flag_1(cont[i], app) == 1)
            break;
        else if (is_flag_c(cont, app, i) == 1)
            break;
        else if (check_m(cont[i], app))
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

