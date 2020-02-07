#include "uls.h"

static void color_file(t_const *cnst) {
    if (cnst->strrwx[3] == 's')
        cnst->color = UIDBIT;
    else if (cnst->strrwx[6] == 's')
        cnst->color = GIDBIT;
    else if (cnst->strrwx[3] == 'x' || cnst->strrwx[6] == 'x' 
             || cnst->strrwx[9] == 'x' || cnst->strrwx[9] == 't') {
        cnst->color = RED;
    }
    else 
        cnst->color = NULL;
}

static void color_dir(t_const *cnst) {
    if (cnst->strrwx[8] == 'w'
        && (cnst->strrwx[9] == 'T' || cnst->strrwx[9] == 't')) {
        cnst->color = STICKYBIT;
    }
    else if (cnst->strrwx[8] == 'w')
        cnst->color = NOTSTICKYBIT;
    else
        cnst->color = DIRCOLOR;
}

void mx_color(t_const *cnst) {
    while (cnst != NULL) {
        if (cnst->strrwx[0] == 's')
            cnst->color = SOCKET;
        else if (cnst->strrwx[0] == 'p')
            cnst->color = PIPE;
        else if (cnst->strrwx[0] == 'l')
            cnst->color = LINK;
        else if (cnst->strrwx[0] == 'b')
            cnst->color = BLOK;
        else if (cnst->strrwx[0] == 'c')
            cnst->color = CHARACTER;
        else if (cnst->strrwx[0] == '-')
            color_file(cnst);
        else if (cnst->strrwx[0] == 'd')
            color_dir(cnst);
        cnst = cnst->next;
    }
}
