#include "uls.h"

void mx_print_l(t_const *cnst, t_data *data) {
    int i = 0;

    printf("total %d\n", data->total);
    while (cnst != NULL) {
        printf("%s", cnst->strrwx);
        cnst->stracl != NULL ? printf("%s", cnst->stracl) : printf(" "); //ACL
        for (i = mx_strlen(cnst->strlinkcount); i < data->max_len_link + 1; i++)
            printf(" ");;
        printf("%s", cnst->strlinkcount);
        printf(" ");
        printf("%s", cnst->struid);
        for (i = mx_strlen(cnst->struid); i < data->max_len_uid + 2; i++)
            printf(" ");    
        printf("%s", cnst->strgid);
        for (i = mx_strlen(cnst->strgid); i < data->max_len_gid + 2; i++)
            printf(" ");    
        for (i = mx_strlen(cnst->strbytes); i < data->max_len_bytes; i++)
            printf(" ");
        if (data->flag_minmaj && !mx_isspecial(cnst))
            for (i = 0; i < data->max_len_min + data->max_len_maj + 2; i++)
                printf(" "); 
        if (mx_isspecial(cnst)) {
            for (i = mx_strlen(cnst->strmaj); i < data->max_len_maj + 1; i++)
                printf(" ");
            printf("%s", cnst->strmaj);
            printf(",");
            printf(" ");
            for (i = mx_strlen(cnst->strmin); i < data->max_len_min; i++)
                printf(" ");
            printf("%s", cnst->strmin);
        }
        else 
            printf("%s", cnst->strbytes);
        printf(" ");
        printf("%s", cnst->strtime);
        printf(" ");
        printf("%s", cnst->name);
        if (cnst->strrwx[0] == 'l')
            printf(" -> %s", cnst->strlink);
        printf("\n");
        cnst = cnst->next;
    }
}
