
NAME = server

CC = g++

CFLAGS = -Wall -Werror -Wextra

SCR = Parser.cpp main.cpp Server.cpp

OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $@

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
