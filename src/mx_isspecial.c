#include "uls.h"

bool mx_isspecial(t_const *cnst) {
    if (cnst->strrwx[0] == 'c')
        return true;
    return false;
}
