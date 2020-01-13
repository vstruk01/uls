#include "uls.h"

void mx_get_law(struct stat st, t_const *cnst) {
    cnst->strrwx = mx_strnew(9);
    cnst->strrwx[0] = (S_IRUSR & st.st_mode) ? 'r' : '-';        
    cnst->strrwx[1] = (S_IWUSR & st.st_mode) ? 'w' : '-';
    cnst->strrwx[2] = (S_IXUSR & st.st_mode) ? 'x' : '-';
    cnst->strrwx[3] = (S_IRGRP & st.st_mode) ? 'r' : '-';
    cnst->strrwx[4] = (S_IWGRP & st.st_mode) ? 'w' : '-';
    cnst->strrwx[5] = (S_IXGRP & st.st_mode) ? 'x' : '-';
    cnst->strrwx[6] = (S_IROTH & st.st_mode) ? 'r' : '-';
    cnst->strrwx[7] = (S_IWOTH & st.st_mode) ? 'w' : '-';
    cnst->strrwx[8] = (S_IXOTH & st.st_mode) ? 'x' : '-';
     if (S_ISGID & st.st_mode)
        cnst->strrwx[5] = cnst->strrwx[5] == 'x' ? 's' : 'S';
    if (S_ISUID & st.st_mode)
        cnst->strrwx[2] = cnst->strrwx[2] == 'x' ? 's' : 'S';
    if (S_ISVTX & st.st_mode)
        cnst->strrwx[8] = cnst->strrwx[8] == 'x' ? 't' : 'T';
}
