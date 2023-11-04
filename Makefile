NAME 		=	minishell
CC 			=	gcc
FLAGS 		=	-Wall -Wextra -Werror -lreadline -g #-fsanitize=address
RM 			=	rm -rf
LIBFT 		=	lib/libft/libft.a
READLINE 	=	lib/readline

SRC_PATH	=	./src/
SRCS		=	$(SRC_PATH)main.c \
				$(SRC_PATH)utils.c \
				$(SRC_PATH)parse.c \
				$(SRC_PATH)own_split.c \
				$(SRC_PATH)signals.c \
				$(SRC_PATH)builtin1.c \
				$(SRC_PATH)utils_line.c \
				$(SRC_PATH)path_finder.c \
				$(SRC_PATH)exec1.c \
				$(SRC_PATH)ft_echo.c \
				$(SRC_PATH)utils_env_list.c \
				$(SRC_PATH)env.c \
				$(SRC_PATH)ft_env.c \
				$(SRC_PATH)ft_exit.c \
				$(SRC_PATH)ft_pwd.c \
				$(SRC_PATH)ft_unset.c \
				$(SRC_PATH)ft_cd.c \
				$(SRC_PATH)ft_export.c \

OBJ 		=	$(SRCS:.c=.o)

all: $(READLINE) $(LIBFT) $(NAME)

$(READLINE):
	#@cd lib && curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	#@tar -xvf lib/readline-8.2.tar.gz -C lib/
	#@$(RM) lib/readline-8.2.tar.gz
	#@cd lib/readline-8.2 && ./configure --prefix=${PWD}/lib/readline
	#@cd lib/readline-8.2 && make install
	#@$(RM) lib/readline-8.2
	@echo "****   readline ok!    ****"

$(LIBFT):
	@make bonus -C lib/libft
	@echo "****   libft ok!    ****"

$(NAME):$(LIBFT) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) -L${PWD}/lib/readline/lib  -I${PWD}/lib/readline/include/ -lreadline -o $(NAME)
	@echo "****   minishell ok!    ****"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/lib/readline/include/

clean:
	make clean -C lib/libft
	$(RM) $(OBJ)

 fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	#$(RM) $(READLINE)

re:	fclean all

.PHONY: all clean fclean re
