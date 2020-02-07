#include "uls.h"

char *mx_getuser(uid_t uid) {
    struct passwd *pws;
    pws = getpwuid(uid);
    return pws->pw_name;
}
