#include "uls.h"

void mx_flags_g_o(t_data *app, char *cont) {
if (mx_get_char_index(cont, 'g') >= 0)
    app->flags[3] = 1; 
if (mx_get_char_index(cont, 'o') >= 0)
     app->flags[5] = 1;
}

