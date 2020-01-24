#include "uls.h"

static void flags_include_basic(char *cont, t_data *app, int len);
static void turn_flag_l(t_data *app, char *cont, int len);
static int is_flag_1(char cont, t_data *app);
static int is_flag_l(char cont, t_data *app, int len);

void mx_basic_flags(char *cont, t_data *app, int len) {
    int i = 0;

    for (i = mx_strlen(cont) - 1; cont[i]; i--) {
        if (cont[i] == 'C') {
            app->flags[3] = 1;
            break;
        }
        else if (is_flag_1(cont[i], app) == 1) // проверка на flag 1
            break;
        else if (is_flag_l(cont[i], app, len) == 1) // проверка на flag l (если флаг 'o' есть то, всегда выключать флаг 'l')
            break;
        else if (cont[i] == 'o') {
            app->flags[5] = 1;
            break;
        }
    }
    if (cont[i] == 'l' || cont[i] == 'o') {
        flags_include_basic(cont, app, len);
    }
}
static int is_flag_1(char cont, t_data *app) {
    if (cont == '1') {
        app->flags[2] = 1;
        return 1;
    }
    return 0;
}

static int is_flag_l(char cont, t_data *app, int len) {
    if (cont == 'l') {
        app->flags[4] = 1;
        turn_flag_l(app, &cont, len);
        return 1;
    }
    return 0;
}

static void flags_include_basic(char *cont, t_data *app, int len) {
    
        if (mx_memchr(cont, 'h', len))
            app->flags[14] = 1;
        if (mx_memchr(cont, 'T', len))
            app->flags[6] = 1;
        if (mx_memchr(cont, 'u', len))
            app->flags[13] = 1;
}

static void turn_flag_l(t_data *app, char *cont, int len) {
    if (mx_memchr(cont, 'o', len)) {
        app->flags[5] = 1;
        app->flags[4] = 0;
    }
}

