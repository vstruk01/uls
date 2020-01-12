#include "uls.h"

void mx_get_size_bytes(struct stat st, t_data *data) {
    data->size_bytes = st.st_size;
}
