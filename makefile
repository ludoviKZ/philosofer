FILES = main.c initiate.c routine.c utils.c validate.c
OBJ = $(FILES:.c=.o)
NAME = philo
CFLAGS = -Wall -Wextra -Werror -g
CC = cc
RM = rm -f
TREAD = -lpthread

%.o : %.c
	$(CC) $(CFLAGS) -Imlx -c -o $@ $<

all:$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(TREAD) -o $(NAME)
	
clean:
	${RM} $(OBJ)

fclean: clean
	${RM} $(NAME)

re: fclean all

.PHONY: all clean fclean re
