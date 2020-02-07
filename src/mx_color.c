#include "uls.h"

static void color_file(t_const *cnst) {
    if (cnst->strrwx[3] == 's')
        cnst->color = MX_UIDBIT;
    else if (cnst->strrwx[6] == 's')
        cnst->color = MX_GIDBIT;
    else if (cnst->strrwx[3] == 'x' || cnst->strrwx[6] == 'x' 
             || cnst->strrwx[9] == 'x' || cnst->strrwx[9] == 't') {
        cnst->color = MX_RED;
    }
    else 
        cnst->color = NULL;
}

static void color_dir(t_const *cnst) {
    if (cnst->strrwx[8] == 'w'
        && (cnst->strrwx[9] == 'T' || cnst->strrwx[9] == 't')) {
        cnst->color = MX_STICKYBIT;
    }
    else if (cnst->strrwx[8] == 'w')
        cnst->color = MX_NOTSTICKYBIT;
    else
        cnst->color = MX_DIRCOLOR;
}

void mx_color(t_const *cnst) {
    while (cnst != NULL) {
        if (cnst->strrwx[0] == 's')
            cnst->color = MX_SOCKET;
        else if (cnst->strrwx[0] == 'p')
            cnst->color = MX_PIPE;
        else if (cnst->strrwx[0] == 'l')
            cnst->color = MX_LINK;
        else if (cnst->strrwx[0] == 'b')
            cnst->color = MX_BLOK;
        else if (cnst->strrwx[0] == 'c')
            cnst->color = MX_CHARACTER;
        else if (cnst->strrwx[0] == '-')
            color_file(cnst);
        else if (cnst->strrwx[0] == 'd')
            color_dir(cnst);
        cnst = cnst->next;
    }
}
