NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror -L/usr/local/lib -I/usr/local/include -lreadline
SRCS = ./main.c ./utils.c ./parse.c ./own_split.c
OBJ = $(SRCS:.c=.o)
RM = rm -rf
LIBFT = libft/libft.a

$(NAME):$(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(FLAGS) $(LIBFT) -o $(NAME)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft/

clean:
	make clean -C libft/
	${RM} $(OBJ)

fclean: clean
	${RM} ${NAME}
	${RM} $(LIBFT)

re:			fclean all

.PHONY: all clean fclean re
