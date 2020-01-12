#include "uls.h"

void mx_get_time(struct stat st, t_data *data){
    data->time = st.st_mtime;
    data->strtime = ctime(&data->time);
}
