#include "uls.h"

int mx_flag_link(t_data *data) {
    if (data->flags[3] || data->flags[5] 
        || data->flags[4] || data->flags[7]) {
        return 1;
    }
    return 0;
}
