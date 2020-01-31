NAME = uls

SRCD = src
INCD = inc
OBJD = obj
LBMXD = libmx

LMBX = libmx.a
INC = uls.h
SRC = main.c \
mx_read_dir.c \
mx_num_file.c \
mx_sort_dir_alp.c \
mx_sort_dir.c \
mx_check_control_char.c \
mx_columns.c \
mx_print_file.c \
mx_print_to_file.c \
mx_head_size.c \
mx_get_result.c \
mx_size_all.c \
mx_read_link.c \
mx_sort_file.c \
mx_get_time.c \
mx_get_ino.c \
mx_get_link.c \
mx_get_uid.c \
mx_get_gid.c \
mx_get_blocks.c \
mx_get_law.c \
mx_get_flag_l.c \
mx_get_size_bytes.c \
mx_get_dev.c \
mx_get_rdev.c \
mx_get_minmaj.c \
mx_get_acl.c \
mx_isspecial.c \
mx_islink.c \
mx_print_l.c \
mx_sort_my_list.c \
mx_print_spase.c \
mx_printstr_update.c \
mx_control_char_name.c \
mx_itoa_sp.c \
mx_full_path.c \
mx_sort_revers.c \
mx_sort_all.c \
mx_get_data.c \
mx_sort_size.c \
mx_read_flags.c \
mx_count_flags_in_str.c \
mx_dir_arr.c \
mx_printerr.c \
mx_print_error.c \
mx_check_flags.c \
mx_basic_flags.c \
mx_flags_for_sort.c \
mx_other_flags.c \
mx_printerr_char.c \
mx_flags_into_arr.c \
mx_get_is.c \
mx_creat_list.c \
mx_sort_time.c \
mx_get_file_col.c \
mx_many_argument.c \
mx_error_print.c \
mx_file_argument.c \
mx_dir_argument.c \
mx_last_char.c \
mx_sort_dir_arr.c \
mx_one_argument.c \
mx_flag_link.c \

INCLUDE = -I $(LBMXD) \
	-I $(INCD) \

LBMXS = $(addprefix $(LBMXD)/, $(LMBX))
INCS = $(addprefix $(INCD)/, $(INC))
SRCS = $(addprefix $(SRCD)/, $(SRC))
OBJS = $(addprefix $(OBJD)/, $(SRC:%.c=%.o))
	
CFLAGS = -std=c99 $(addprefix -W, all extra error pedantic)
CC = clang

all: $(NAME)

install: $(NAME) clean

$(LBMXS):
	@make -sC $(LBMXD)

$(NAME): $(OBJS) $(LBMXS)
	@$(CC) $(CFLAGS) $(LBMXS) $(OBJS) -o $@
	@printf "\x1b[32;1m$@ created\x1b[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)
	@printf "\x1b[32mcompiled: \x1b[0m[$(<:$(SRCD)/%.c=%.c)]\n"

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

uninstall: clean
	@make -sC $(LBMXD) $@
	@rm -rf $(NAME)
	@printf "\x1b[34;1mdeleted $(NAME)\x1b[0m\n"

clean:
	@make -sC $(LBMXD) $@
	@rm -rf $(OBJD)
	@printf "\x1b[34;1mdeleted $(OBJD)\x1b[0m\n"

reinstall: uninstall install