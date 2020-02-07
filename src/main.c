#include "uls.h"

int main(int argc, char **argv) {
    t_data *data = malloc(sizeof(t_data));
    char **argv2 =mx_strarr(argc,argv);

    mx_read_flags(argv, argc, data);
     if(data->flags[18] == 1){
     	int return_value =mx_flag_r(argc,argv2);
     	return return_value;
     }
    if (!data->dir_arr[0])
        mx_one_argument(data);
    else
        mx_many_argument(data);
    if (data->errors)
        return 1;
    return 0;
}
