#include "uls.h"

void mx_get_ino(struct stat st, t_const *cnst) {
    cnst->ino = st.st_ino;
}
