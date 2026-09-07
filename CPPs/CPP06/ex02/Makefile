NAME = Identify
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic

SRC = main.cpp Base.cpp
OBJ = $(SRC:.cpp=.o)




all: $(NAME)

$(NAME): $(OBJ)
		$(CXX)  $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf	$(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re