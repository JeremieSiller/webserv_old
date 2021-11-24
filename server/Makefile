
NAME = server

CC = clang++

CFLAGS = -Wall -Werror -Wextra

SCR = Parser.cpp main.cpp Server.cpp

OBJ = $(SRC:.cpp=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SCR) -o $@

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
