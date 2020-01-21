#include "uls.h"

static void print(t_data *data, t_const *cnst);

void mx_print_l(t_const *cnst, t_data *data) {
    mx_control_char_name(&cnst->name);
    mx_printstr_update("total ", data->strtotal, "\n", NULL, NULL);
    while (cnst != NULL) {
        if (data->flags[7]) {
            mx_print_spase(data->max_len_ino - mx_strlen(cnst->strino));
            mx_printstr_update(cnst->strino, " ", NULL, NULL, NULL);
        }
        if (data->flags[8]) {
            mx_print_spase(data->max_len_blocks - mx_strlen(cnst->strblocks));
            mx_printstr_update(cnst->strblocks, " ", NULL, NULL, NULL);
        }
        mx_printstr(cnst->strrwx);
        cnst->stracl != NULL ? mx_printstr(cnst->stracl) : mx_printstr(" ");
        mx_print_spase(data->max_len_link - mx_strlen(cnst->strlinkcount) + 1);
        mx_printstr_update(cnst->strlinkcount, " ", cnst->struid, NULL, NULL);
        print(data, cnst);
        cnst = cnst->next;
    }
}

static void print(t_data *data, t_const *cnst) {
    mx_print_spase(data->max_len_uid - mx_strlen(cnst->struid) + 2);
    if (!data->flags[5]) {
        mx_printstr(cnst->strgid);
        mx_print_spase(data->max_len_gid - mx_strlen(cnst->strgid) + 2);
    }
    mx_print_spase(data->max_len_bytes - mx_strlen(cnst->strbytes));
    if (data->flag_minmaj && !mx_isspecial(cnst))
        mx_print_spase(data->max_len_min + data->max_len_maj + 2);
    if (mx_isspecial(cnst)) {
        mx_print_spase(data->max_len_maj - mx_strlen(cnst->strmaj) + 1);
        mx_printstr_update(cnst->strmaj, ",", " ", NULL, NULL);
        mx_print_spase(data->max_len_min - mx_strlen(cnst->strmin));
        mx_printstr(cnst->strmin);
    }
    else 
        mx_printstr(cnst->strbytes);
    mx_printstr_update(" ", cnst->strtime, " ", cnst->name, NULL);
    if (cnst->strrwx[0] == 'l')
        mx_printstr_update(" -> ", cnst->strlink, NULL, NULL, NULL);
    mx_printstr("\n");
}
