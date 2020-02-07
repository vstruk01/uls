#include "uls.h" 

static void print_and_sort(t_data *data, t_const *cnst) {
    cnst = data->cnst;
    mx_get_is(cnst, data);
    mx_num_file(cnst, data);
    mx_get_file_col(cnst, data);
    data->flag_total = 0;
    if (data->flags[4] || data->flags[5] || data->flags[3])
        mx_print_l(cnst, data);
    else if (data->flags[14]) {
        mx_print_m(data);
        if (data->dir->name != NULL)
            mx_printstr(", ");
        mx_printchar('\n');
    }
    else
        mx_print_file(data);
}

static t_sort *new_nod(t_sort *gen, t_const *cnst, t_data *data) {
    gen->next = malloc(sizeof (t_sort));
    gen = gen->next;
    mx_get_flag_l(cnst, data);
    gen->cnst = cnst;
    gen->next = NULL;
    return gen;
}

void mx_file_argument(t_const *cnst, t_data *data) {
    t_sort *gen = malloc(sizeof (t_sort));
    t_sort *save = gen;

    data->cnst = cnst;
    gen->cnst = NULL;
    while (cnst != NULL) {
        data->size++;
        cnst->ful_n = NULL;
        if (gen->cnst == NULL) {
            mx_get_flag_l(cnst, data);
            gen->cnst = cnst;
            gen->next = NULL;
        }
        else
            gen = new_nod(gen, cnst, data);
        cnst = cnst->next;
    }
    gen = save;
    mx_sort_all(data, gen);
    print_and_sort(data, cnst);
}
