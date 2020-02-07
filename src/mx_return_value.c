#include "uls.h"


int mx_return_value(int argc, char **argv) {
    int index = mx_argv_index(argc, argv);

    if (index == 0)
        return 0;

    int error_occured = 0;
    for (int i = index; i < argc; ++i) {
        if (mx_error_printer(argv[i]) )
            error_occured += 1;
    }

    if(error_occured > 0)
        return 1;
    return 0;
}
