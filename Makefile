SRC = read_dir \
num_file \
check_control_char \
columns \
print_file \
head_size \
print_file_return_dir \
get_result \
size_all \
sort_file \


INC = uls.h
INCMX = libmx.h

SRCS = $(addsuffix .c, $(addprefix mx_, $(SRC)))
OBJO = $(SRCS:.c=.o)
FILE = uls
LIBL = libmx.a
NAME = uls.a
SRCM = main.c
DEL = libmx.h.gch 

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean 

install:
	@cd libmx && make -f Makefile install 
	@mkdir -p obj
	@cp $(addprefix src/, $(SRCM)) .
	@cp $(addprefix src/, $(SRCS)) .
	@cp $(addprefix inc/, $(INC)) .
	@cp $(addprefix libmx/inc/, $(INCMX)) .	
	@cp $(addprefix libmx/, $(LIBL)) .
	@clang $(CFLAGS) -c $(SRCS) $(INCMX)
	@ar -rc $(NAME) $(OBJO)
	@clang $(CFLAGS) -o $(FILE) $(SRCM) $(NAME) $(LIBL)
	@mv $(SRCM) ./obj
	@mv $(OBJO) ./obj
	@mv $(SRCS) ./obj

uninstall:
	@rm -rf $(FILE) 
	@cd libmx && make -f Makefile uninstall

clean:
	@cd libmx && make -f Makefile clean
	@rm -rf obj
	@rm -rf $(INCMX) $(INC) $(SRCM) $(LIBL) $(NAME) $(DEL) $(SRCS) 

reinstall: uninstall all
