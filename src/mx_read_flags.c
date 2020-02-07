#include "uls.h"

void mx_read_flags(char **argv, int argc, t_data *app) {
    app->dir_arr = NULL;
    app->path = NULL;
    app->errors = 0;
    app->total = 0;
    app->max_len_uid = 0;
    app->max_len_gid = 0;
    app->max_len_bytes = 0;
    app->max_len_link = 0;
    app->max_len_min = 0;
    app->max_len_maj = 0;
    app->max_len_ino = 0;
    app->max_len_blocks = 0;
    app->max_len_min = 3;
    app->max_len_maj = 4;
    app->isattyflag = 0;
    app->max_len_flags = 0;
    app->len_ttr = 0;
    mx_count_flags_in_str(argv, app, argc);
}
