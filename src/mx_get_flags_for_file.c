#include "uls.h"

static void get_flags(t_const *cnst, char *str) {
    char *tmp = NULL;

    tmp = cnst->flags;
    if (cnst->flags != NULL) {
        cnst->flags = mx_strjoin(tmp, ",");
        free(tmp);
    }
    tmp = cnst->flags;
    cnst->flags = mx_strjoin(tmp, str);
    free(tmp);
}

static void root_flags(t_const *cnst, struct stat st) {
    if (st.st_flags & SF_NOUNLINK) // sunlnk
        get_flags(cnst, "sunlnk");
    if (st.st_flags & SF_RESTRICTED) // restricted
        get_flags(cnst, "restricted");
    if (st.st_flags & UF_HIDDEN) // hidden
        get_flags(cnst, "hidden");
    if (st.st_flags & UF_COMPRESSED) // compressed 
        get_flags(cnst, "compressed");
}

static void user_flags(t_const *cnst, struct stat st) {
    if (st.st_flags & UF_APPEND) // uappnd
        get_flags(cnst, "uappnd");
    if (st.st_flags & UF_IMMUTABLE) //uchg
        get_flags(cnst, "uchg");
    if (st.st_flags & UF_NODUMP) //nodump
        get_flags(cnst, "nodump");
    if (st.st_flags & UF_OPAQUE) // opaque
        get_flags(cnst, "opaque");
}

void mx_get_flags_for_file(t_const *cnst, struct stat st) {
    cnst->flags = NULL;
    user_flags(cnst, st);
    root_flags(cnst, st);
    if (cnst->flags == NULL)
        cnst->flags = "-";
}
