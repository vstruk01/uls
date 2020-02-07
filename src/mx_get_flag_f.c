#include "uls.h"

static void file(t_const *cnst) {
    if (cnst->strrwx[3] == 's' || cnst->strrwx[6] == 's')
        cnst->flag_f = "*";
    else if (cnst->strrwx[3] == 'x' || cnst->strrwx[6] == 'x' 
             || cnst->strrwx[9] == 'x' || cnst->strrwx[9] == 't') {
        cnst->flag_f = "*";
    }
    else 
        cnst->flag_f = NULL;
}

void mx_get_flag_f(t_const *cnst) {
    while (cnst != NULL) {
        if (cnst->strrwx[0] == 's')
            cnst->flag_f = "=";
        else if (cnst->strrwx[0] == 'p')
            cnst->flag_f = "|";
        else if (cnst->strrwx[0] == 'l')
            cnst->flag_f = "@";
        else if (cnst->strrwx[0] == 'b' || cnst->strrwx[0] == 'c')
            cnst->flag_f = NULL;
        else if (cnst->strrwx[0] == '-')
            file(cnst);
        else if (cnst->strrwx[0] == 'd')
            cnst->flag_f = "/";
        cnst = cnst->next;
    }
}
