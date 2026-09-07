SRC = main.cpp newZombie.cpp randomChump.cpp Zombie.cpp 
OBJ = $(SRC:.cpp=.o)
NAME = Zombie
CC = c++ -Wall -Wextra -Werror -std=c++98 -pedantic

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(OBJ) -o $(NAME)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf	$(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re