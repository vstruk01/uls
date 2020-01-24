#include "uls.h"

static void get_spases(char **str, int number);
static void flag_i(t_const *cnst, t_data *data, int ino, int blocks);
static void flag_s(t_const *cnst, t_data *data, int ino, int blocks);
static void flag_is(t_const *cnst, t_data *data, int ino, int blocks);

void mx_get_is(t_const *cnst, t_data *data) {
    int ino = 0;
    int blocks = 0;

    if (data->flags[8] && data->flags[7])
        flag_is(cnst, data, ino, blocks);
    else if (data->flags[8])
        flag_s(cnst, data, ino, blocks);
    else if (data->flags[7])
        flag_i(cnst, data, ino, blocks);
    else
        while (cnst != NULL) {
            cnst->name_c = cnst->name;
            cnst = cnst->next;
        }
}

static void flag_i(t_const *cnst, t_data *data, int ino, int blocks) {
    char *str = NULL;

    while (cnst != NULL) {
        ino = data->max_len_ino;
        blocks = data->max_len_blocks;
        str = mx_strnew(ino + 1);
        get_spases(&str, ino - mx_strlen(cnst->strino));
        mx_strcat(str, cnst->strino);
        mx_strcat(str, " ");
        cnst->name_c = mx_strjoin(str, cnst->name);
        free(str);
        cnst = cnst->next;
        str = NULL;
    }
}

static void flag_s(t_const *cnst, t_data *data, int ino, int blocks) {
    char *str = NULL;

    while (cnst != NULL) {
        ino = data->max_len_ino;
        blocks = data->max_len_blocks;
        str = mx_strnew(blocks + 1);
        get_spases(&str, blocks - mx_strlen(cnst->strblocks));
        mx_strcat(str, cnst->strblocks);
        mx_strcat(str, " ");
        cnst->name_c = mx_strjoin(str, cnst->name);
        free(str);
        str = NULL;
        cnst = cnst->next;
    }
}

static void flag_is(t_const *cnst, t_data *data, int ino, int blocks) {
    char *str = NULL;

    while (cnst != NULL) {
        ino = data->max_len_ino;
        blocks = data->max_len_blocks;
        str = mx_strnew(blocks + ino + 2);
        get_spases(&str, ino - mx_strlen(cnst->strino));
        mx_strcat(str, cnst->strino);
        get_spases(&str, blocks - mx_strlen(cnst->strblocks) + 1);
        mx_strcat(str, cnst->strblocks);
        mx_strcat(str, " ");
        cnst->name_c = mx_strjoin(str, cnst->name);
        free(str);
        str = NULL;
        cnst = cnst->next;
    }
}

static void get_spases(char **str, int number) {
    for (int i = 0; i < number; i++)
        mx_strcat(*str, " ");    
}
