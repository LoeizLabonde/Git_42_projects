# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 16:39:54 by llabonde          #+#    #+#              #
#    Updated: 2024/08/19 17:07:40 by llabonde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= so_long
FLAGSE			= -fsanitize=address
FLAGS			= -Wextra -Werror -Wall -I -g3 #${FLAGSE}

MLXFLAGS		= -Imlx_linux -lXext -lX11 -lm -lz

SRCS			=	so_long.c \
					check.c \
					check_solvability.c \
					utils.c \
					imgs.c \
					maps_funct.c \
					render.c \
					move.c
			
DIR_MLX 		= mlx-linux/
MLX				= $(addprefix $(DIR_MLX), libmlx.a)

DIR_LIBFT		= Libft/
LIBFT			= $(addprefix $(DIR_LIBFT), libft.a)

OBJS 			= ${SRCS:%.c=./build/%.o}

HEADER			= includes/so_long.h

all: 			${NAME}

${NAME}:		${OBJS} ${LIBFT} ${MLX}
				${CC} $^ ${FLAGS} ${MLXFLAGS} -o ${NAME}

./build/%.o:	./sources/%.c ${HEADER}
				@mkdir -p build
				${CC} ${FLAGS} -Imlx_linux -c $< -o $@

${MLX}:			FORCE
				make -s -C ${DIR_MLX}

${LIBFT}:		FORCE
				make -s -C ${DIR_LIBFT}

clean:
				${RM} -r ./build
				${RM} -r ./build_bonus

fclean:			clean
				${RM} ${NAME}
				${RM} so_long_bonus
				make -s -C ${DIR_MLX} clean
				make -s -C ${DIR_LIBFT} clean

re:				fclean
				${MAKE} all
			
FORCE:

.PHONY: all clean fclean re FORCE