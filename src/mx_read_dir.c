#include "uls.h"

static void print_error(t_data *data, char *name, t_sort *gen) {
    struct stat st;

    stat(name, &st);
    if (S_IFDIR == (S_IFMT & st.st_mode))
        while (mx_get_char_index(name, '/') >= 0)
            name++;
    mx_print_error("uls: ");
    mx_print_error(name);
    mx_print_error(": ");
    mx_print_error(strerror(errno));
    mx_print_error("\n");
    data->errors = 1;
    free(gen);
}

static t_sort *get_name(struct dirent *entry, t_data *data, t_sort *gen) {
    gen->next = malloc(sizeof (t_sort));
    gen->next->cnst = malloc(sizeof (t_const));
    gen->next->cnst->name = mx_strdup(entry->d_name);
    if (data->path !=  NULL) {
        char *tmp = mx_strjoin(data->path, "/");

        gen->next->cnst->ful_n = mx_strjoin(tmp, gen->next->cnst->name);
        free(tmp);
    }
    else
        gen->next->cnst->ful_n = NULL;
    mx_get_flag_l(gen->next->cnst, data);
    data->size += 1;
    gen = gen->next;
    gen->next = NULL;
    return gen;
}

static void flag_A(DIR *dir, t_data *data, t_sort *gen) {
    struct dirent *entry = NULL;

    while ((entry = readdir(dir)) != NULL) {
        if (mx_strcmp(entry->d_name, ".") != 0 
            && mx_strcmp(entry->d_name, "..") != 0) {
            gen = get_name(entry, data, gen);
        }
    }
}

static void flag_a_A(DIR *dir, t_data *data, t_sort *gen) {
    struct dirent *entry = NULL;

    data->flag_total = 1;
    if (data->flags[23]) {
        entry = readdir(dir);
        gen = get_name(entry, data, gen);
    }
    else if (data->flags[0])
        while ((entry = readdir(dir)) != NULL)
            gen = get_name(entry, data, gen);
    else if (data->flags[1])
        flag_A(dir, data, gen);
    else
        while ((entry = readdir(dir)) != NULL)
            if (entry->d_name[0] != '.')
                gen = get_name(entry, data, gen);
    closedir(dir);
}

int mx_read_dir(char *dirname, t_data *data) {
    DIR *dir = opendir(dirname);
    t_sort *general = malloc(sizeof(t_sort));
    t_sort *tmp = NULL;

    if (!dir) {
        print_error(data, dirname, general);
        return 0;
    }
    general->next = NULL;
    flag_a_A(dir, data, general);
    tmp = general;
    general = general->next;
    free(tmp);
    if (general == NULL)
        return 0;
    mx_sort_all(data, general);
    mx_get_is(data->cnst, data);
    mx_num_file(data->cnst, data);
    mx_get_file_col(data->cnst, data);
    return 1;
}
