NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror -lreadline -g
SRCS = ./main.c ./utils.c ./parse.c ./own_split.c
OBJ = $(SRCS:.c=.o)
RM = rm -rf
LIBFT = libft/libft.a
READLINE = readline

all: $(READLINE) $(LIBFT) $(NAME)

$(READLINE):
	@curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	@tar -xvf readline-8.2.tar.gz
	@${RM} readline-8.2.tar.gz
	@cd readline-8.2 && ./configure --prefix=${PWD}/readline
	@cd readline-8.2 && make install
	@${RM} readline-8.2
	@echo "****   readline ok!    ****"

$(LIBFT):
	@make -C libft/
	@echo "****   libft ok!    ****"

$(NAME):$(LIBFT) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) -L${PWD}/readline/lib  -I${PWD}/readline/include/ -lreadline -o $(NAME)
	@echo "****   minishell ok!    ****"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/readline/include/

clean:
	make clean -C libft/
	${RM} $(OBJ)

 fclean: clean
	${RM} ${NAME}
	${RM} $(LIBFT)
	${RM} $(READLINE)

re:	fclean all

.PHONY: all clean fclean re
