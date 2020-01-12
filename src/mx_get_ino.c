#include "uls.h"

void mx_get_ino(struct stat st, t_data *data) {
    data->ino = st.st_ino;
}
