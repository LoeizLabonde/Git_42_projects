NAME = cub3D

CUBE_DIR = ./srcs/cub
SRC = main.c game.c map.c player.c texture.c create_map.c keys.c utils.c utils2.c create_images.c free.c ft_player_coll.c \
	  init/init_window.c init/init_minimap.c init/init.c init/init_img.c init/init_raycast.c \
	  parsing/fill_data.c parsing/fill_color_textures.c parsing/parse_data.c parsing/parse_map.c parsing/parsing.c parsing/parsing_utils.c parsing/check_end_of_file.c \
	  draw/draw.c draw/draw_minimap.c draw/ft_draw_ray.c draw/ft_block.c 

GNL_DIR = ./srcs/gnl/
SRC_GNL = get_next_line.c get_next_line_utils.c


LIBFT_DIR = ./srcs/libft/
SOURCES_LIBFT = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_memset.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_bzero.c\
	ft_strlcpy.c ft_strlcat.c ft_strlen.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_strnstr.c ft_atoi.c \
	ft_strdup.c ft_calloc.c\
	ft_substr.c ft_strjoin.c ft_itoa.c ft_split.c ft_strtrim.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \

INCLUDE = ./include/

OBJ_DIR = obj
OBJECTS_CUBE = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJECTS_GNL = $(SRC_GNL:%.c=$(OBJ_DIR)/%.o)
OBJECTS_LIBFT = $(SOURCES_LIBFT:%.c=$(OBJ_DIR)/%.o)
OBJ =  $(OBJECTS_CUBE) $(OBJECTS_LIBFT) $(OBJECTS_GNL)


MLX_PATH = /home/kduroux/sgoinfre/minilibx-linux
#MLX_PATH = /home/llabonde/sgoinfre/minilibx-linux
#MLX_PATH = /home/vboxuser/minilib/minilibx-linux

CCFLAGS = $(CC) -Wextra -Wall -Werror -g3
LMFLAGS = -lmlx -lXext -lX11 -lm -lz -ffast-math -flto -Ofast -funroll-loops -fomit-frame-pointer

BRED = \033[1;31m
RED  = \033[0;31m
BGRN = \033[1;32m
GRN  = \033[0;32m
YEL  = \033[0;33m
BYEL = \033[1;33m
BLU  = \033[0;34m
BBLU = \033[1;34m
BMAG = \033[1;35m
MAG  = \033[0;35m
CYN  = \033[0;36m
BCYN = \033[1;36m
BWHT = \033[1;37m
NC   = \033[0m

all: create_dir $(OBJ) $(NAME)

create_dir:
	@if [ ! -d $(OBJ_DIR) ]; then \
		mkdir -p $(OBJ_DIR); \
		echo "$(BRED)Created directory $(OBJ_DIR) -> $(GRN)[OK]$(NC)"; \
	fi
	
$(NAME): $(OBJ)
	@echo "$(BBLU)Creating Binary $(NAME) -> $(GRN)[OK]$(NC)"
	@$(CCFLAGS) $(OBJ) -L$(MLX_PATH) $(LMFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(CUBE_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BMAG)Compiling $< -> $(GRN)[OK]$(NC)"
	@$(CCFLAGS) -I$(MLX_PATH) -I $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIBFT_DIR)%.c
	@echo "$(BCYN)Compiling $< -> $(GRN)[OK]$(NC)"
	@$(CCFLAGS) -I$(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o: $(GNL_DIR)%.c
	@echo "$(RED)Compiling $< -> $(GRN)[OK]$(NC)"
	@$(CCFLAGS) -I$(MLX_PATH) -I $(INCLUDE) -c $< -o $@

clean:
	@echo "$(BRED)Cleaning up... -> $(GRN)[OK]$(NC)"
	@rm -rf $(OBJ) $(OBJ_DIR)

fclean: clean
	@echo "$(BRED)Removing $(NAME) and all -> $(GRN)[OK]$(NC)"
	@#make clean -C mlx/
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re create_dir
