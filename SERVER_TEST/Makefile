
NAME = serv

CC = clang++

# CFLAGS = -Wall -Werror -Wextra

SCR = server.cpp main.cpp

OBJ = $(SRC:.cpp=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SCR) -o $@

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
