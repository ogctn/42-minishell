NAME	=	minishell
CC		=	gcc
FLAGS	=	#-g -fsanitize=address#-Wall -Wextra -Werror
RM		=	rm -rf
LIBFT	=	lib/libft/libft.a
RDLINE	=	lib/readline

SRC_DIR	=	src
SRCS	=	$(SRC_DIR)/main.c \
			$(SRC_DIR)/parse/parse.c \
			$(SRC_DIR)/parse/utils.c \
			$(SRC_DIR)/parse/own_split.c \
			$(SRC_DIR)/parse/utils_line.c \
			$(SRC_DIR)/parse/assign_type.c \
			$(SRC_DIR)/parse/dollar_sign.c \
			$(SRC_DIR)/parse/delete_quotes.c \
			$(SRC_DIR)/exec/exec1.c \
			$(SRC_DIR)/exec/path_finder.c \
			$(SRC_DIR)/exec/signals.c \
			$(SRC_DIR)/builtin/env.c \
			$(SRC_DIR)/builtin/utils_env_list.c \
			$(SRC_DIR)/builtin/builtin1.c \
			$(SRC_DIR)/builtin/ft_echo.c \
			$(SRC_DIR)/builtin/ft_cd.c \
			$(SRC_DIR)/builtin/ft_env.c \
			$(SRC_DIR)/builtin/ft_exit.c \
			$(SRC_DIR)/builtin/ft_export.c \
			$(SRC_DIR)/builtin/ft_pwd.c \
			$(SRC_DIR)/builtin/ft_unset.c \
			$(SRC_DIR)/redirections/redir.c

OBJ_DIR	=	obj
OBJS	=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all		:	$(NAME) #install_readline $(NAME)

$(NAME)	:	$(OBJ_DIR) $(OBJS)
	@make bonus -C lib/libft
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -lreadline -L${PWD}/$(RDLINE)/lib  -I${PWD}/$(RDLINE)/include/ -o $(NAME)
	@echo "****   minishell ok!    ****"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parse
	@mkdir -p $(OBJ_DIR)/exec
	@mkdir -p $(OBJ_DIR)/builtin
	@mkdir -p $(OBJ_DIR)/redirections

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/lib/readline/include/

install_readline	:
	@cd lib && curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	@tar -xvf lib/readline-8.2.tar.gz -C lib/
	@$(RM) lib/readline-8.2.tar.gz
	@cd lib/readline-8.2 && ./configure --prefix=${PWD}/$(RDLINE)
	@cd lib/readline-8.2 && make install
	@$(RM) lib/readline-8.2
	@echo "****   readline ok!    ****"

clean:
	make clean -C lib/libft
	$(RM) $(OBJ_DIR)

fclean	:	clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	$(RM) $(RDLINE)

re: fclean all

git_me: install_readline $(NAME)

tn: all clean
	./$(NAME)

.PHONY: all clean fclean re
