#include "uls.h"

static void get_xattr(t_const *cnst, char *name, acl_t acl) {
    char *buf = mx_strnew(1024);

    listxattr(name, buf, 1024, XATTR_NOFOLLOW);
    cnst->strxattr = buf;
    cnst->xattr = getxattr(name, buf, NULL, 1024, 1024, XATTR_NOFOLLOW);
    cnst->inoattr = mx_itoa(cnst->xattr);
    if (acl != NULL)
        cnst->acltext = acl_to_text(acl, NULL);
    cnst->stracl = "@";
}

void mx_get_acl(t_const *cnst) {
    acl_t acl = NULL;
    ssize_t attr = 0;
    char *name = cnst->ful_n == NULL ? cnst->name : cnst->ful_n;

    cnst->strxattr = NULL;
    cnst->acltext = NULL;
    cnst->stracl = NULL;
    cnst->xattr = 0;
    cnst->inoattr = NULL;
    attr = listxattr(name, NULL, 0, XATTR_NOFOLLOW);
    acl = acl_get_file(name, ACL_TYPE_EXTENDED);
    if (attr > 0) {
        get_xattr(cnst, name, acl);
        acl_free(acl);
    }
    else if (acl != NULL) {
        cnst->acltext = acl_to_text(acl, NULL);
        cnst->stracl = mx_strdup("+");
        acl_free(acl);
    }
}
