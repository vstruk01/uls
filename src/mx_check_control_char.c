#include "uls.h"

void mx_check_control_char(t_data *data) {
    for (int i = 0; (data->d_name)[i] != NULL; i++)
        for (int j = 0; (data->d_name)[i][j] != '\0'; j++)
            if ((data->d_name)[i][j] == '\t' 
                || (data->d_name)[i][j] == '\n'
                || (data->d_name)[i][j] == '\r' 
                || (data->d_name)[i][j] == '\f'
                || (data->d_name)[i][j] == '\a'
                || (data->d_name)[i][j] == '\b'
                || (data->d_name)[i][j] == '\v'
                || (data->d_name)[i][j] == '\033')
            {
                (data->d_name)[i][j] = '?';
            } 
}
