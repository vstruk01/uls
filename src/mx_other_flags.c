#include "uls.h"

void mx_other_flags(char *cont, t_data *app) {
    if (mx_get_char_index(cont, 's') >= 0)
        app->flags[8] = 1; 
    if (mx_get_char_index(cont, 'i') >= 0)
        app->flags[7] = 1;
    if (mx_get_char_index(cont, 'd') >= 0)
        app->flags[23] = 1;
    else if (mx_get_char_index(cont, 'f') >= 0) {
        app->flags[9] = 1;
        app->flags[0] = 1;
    }
    else if (mx_get_char_index(cont, 'a') >= 0)
        app->flags[0] = 1;
    else if (mx_get_char_index(cont, 'A') >= 0)
        app->flags[1] = 1;
    if (mx_get_char_index(cont, 'G') >= 0)
        app->flags[16] = 1;
    if (mx_get_char_index(cont, 'F') >= 0)
        app->flags[19] = 1;
    else if (mx_get_char_index(cont, 'p') >= 0)
        app->flags[20] = 1;
}
