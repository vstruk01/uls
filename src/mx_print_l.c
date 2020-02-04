#include "uls.h"

static void pritn2(t_data *data, t_const *cnst) {
    if (data->flags[8]) {
        mx_print_spase(data->max_len_blocks - mx_strlen(cnst->strblocks));
        mx_printstr_update(cnst->strblocks, " ", NULL, NULL);
    }
    mx_printstr(cnst->strrwx);
    cnst->stracl != NULL ? mx_printstr(cnst->stracl) : mx_printstr(" ");
    mx_print_spase(data->max_len_link - mx_strlen(cnst->strlinkcount) + 1);
    mx_printstr_update(cnst->strlinkcount, " ", NULL, NULL);
    if (!data->flags[3]) {
        mx_printstr(cnst->struid);
        mx_print_spase(data->max_len_uid - mx_strlen(cnst->struid) + 2);
    }
    if (data->flags[5] && data->flags[3])
        mx_printstr("  ");
    if (!data->flags[5]) {
        mx_printstr(cnst->strgid);
        mx_print_spase(data->max_len_gid - mx_strlen(cnst->strgid) + 2);
    }
}

static void print(t_data *data, t_const *cnst) {
    if (data->flag_minmaj && !mx_isspecial(cnst))
        mx_print_spase(8 - data->max_len_bytes);
    if (mx_isspecial(cnst)) {
        mx_print_spase(data->max_len_maj - mx_strlen(cnst->strmaj) - 1);
        mx_printstr_update(cnst->strmaj, ",", " ", NULL);
        mx_print_spase(data->max_len_min - mx_strlen(cnst->strmin));
        mx_printstr(cnst->strmin);
    }
    else { 
        mx_print_spase(data->max_len_bytes - mx_strlen(cnst->strbytes));
        mx_printstr(cnst->strbytes);
    }
    mx_printstr_update(" ", cnst->strtime, " ", cnst->color);
    mx_printstr_update(cnst->name, NOCOLOR, NULL, NULL);
    if (mx_islink(cnst) && cnst->strrwx[1] != '-')
        mx_printstr_update(" -> ", cnst->strlink, NULL, NULL);
    mx_printstr("\n");
}

static void permission(t_const *cnst, t_data *data) {
    if (!mx_islink(cnst))
        return;
    if (cnst->strrwx[1] == '-') {
        char *str = NULL;
        char *tmp = NULL;

        if (data->path == NULL)
            str = mx_strjoin("./", cnst->name);
        else {
            tmp = mx_strjoin(data->path, "/");
            str = mx_strjoin(tmp, cnst->name);
            free(tmp);
        }
        mx_print_error("\n");
        mx_print_error("uls: ");
        mx_print_error(str);
        mx_print_error(": Permission denied\n");
        free(str);
    }
}

void mx_print_l(t_const *cnst, t_data *data) {
    if (data->flag_total)
        mx_printstr_update("total ", data->strtotal, "\n", NULL);
    while (cnst != NULL) {
        if (isatty(1) != 0)
            mx_control_char_name(&cnst->name);
        permission(cnst, data);
        if (data->flags[7]) {
            mx_print_spase(data->max_len_ino - mx_strlen(cnst->strino));
            mx_printstr_update(cnst->strino, " ", NULL, NULL);
        }
        pritn2(data, cnst);
        print(data, cnst);
        cnst = cnst->next;
    }
}
