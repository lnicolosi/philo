CC = gcc
NAME = philo
CFLAGS = -Wall -Wextra -Werror -Imlx

SRC = 	dinner.c getters_setters.c init.c main.c monitor.c parsing.c \
		safe_functions.c synchro_utils.c utils.c write.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -g -Imlx -Iincludes -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME)
	rm -rf $(OBJ)

re: fclean all

.PHONY: all clean fclean re