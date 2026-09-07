NAME = push_swap
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
LIBFTDIR = libft/
OBJ_DIR = obj/
SRC_DIR = srcs/

SRC =    push_swap.c \
         algorithm.c \
         ft_add_back.c \
         ft_stack_new.c \
         ft_check_utils.c \
         ft_parse.c \
         solver_utils_ab.c \
         solver_utils_ba.c \
         ft_rotate_and_push.c \
         operations.c \
         operations_2.c \
         operations_3.c \
         ft_check_dup.c \
         ft_check_sorted.c \
         ft_error_print.c \
         ft_free.c \
         lst_utils.c \
         lst_utils_2.c \
         ft_parse_args_quoted.c \
         ft_list_args.c \
         ft_check_args.c \
         ft_sort_big.c \
         ft_sort_three.c \
         ft_rotate_type.c \

OBJ = $(addprefix ${OBJ_DIR}, ${SRC:.c=.o})

INCLUDE = -L ./libft -lft

${OBJ_DIR}%.o: ${SRC_DIR}%.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJ}
	make -C $(LIBFTDIR)
	${CC} ${FLAGS} ${OBJ} -o ${NAME} ${INCLUDE}

all: ${NAME}

clean:
	${RM} ${OBJ}
	@cd $(LIBFTDIR) && $(MAKE) clean

fclean: clean
	${RM} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re
