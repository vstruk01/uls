#include "uls.h"

void mx_get_acl(t_const *cnst) {
    acl_t acl = NULL;
    ssize_t attr = 0;

    cnst->stracl = NULL;
    attr = listxattr(cnst->name, NULL, 0, XATTR_NOFOLLOW);
    acl = acl_get_file(cnst->name, ACL_TYPE_EXTENDED);
    if (attr > 0) {
        cnst->stracl = mx_strdup("@");
        return;
    }
    else if (acl != NULL) {
        cnst->stracl = mx_strdup("+");
        acl_free(acl);
    }
}

