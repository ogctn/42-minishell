NAME	=	"minishell"
CC 		=	gcc
FLAGS 	=	-Wall -Wextra -Werror -g -fsanitize=address
RM 		=	rm -rf
LIBFT 	=	lib/libft/libft.a
RDLINE 	=	lib/readline

SRC_DIR	=	src
SRCS	=	$(SRC_DIR)/main.c \
			$(SRC_DIR)/utils.c \
			$(SRC_DIR)/parse.c \
			$(SRC_DIR)/own_split.c \
			$(SRC_DIR)/signals.c \
			$(SRC_DIR)/builtin1.c \
			$(SRC_DIR)/utils_line.c \
			$(SRC_DIR)/path_finder.c \
			$(SRC_DIR)/exec1.c \
			$(SRC_DIR)/ft_echo.c \
			$(SRC_DIR)/utils_env_list.c \
			$(SRC_DIR)/env.c \
			$(SRC_DIR)/ft_env.c \
			$(SRC_DIR)/ft_exit.c \
			$(SRC_DIR)/ft_pwd.c \
			$(SRC_DIR)/ft_unset.c \
			$(SRC_DIR)/ft_cd.c \
			$(SRC_DIR)/ft_export.c \

OBJ_DIR =	obj
OBJ		=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all		:	$(READLINE) $(LIBFT) $(NAME)

$(LIBFT):
	@make bonus -C lib/libft

$(READLINE):
	#@cd lib && curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	#@tar -xvf lib/readline-8.2.tar.gz -C lib/
	#@$(RM) lib/readline-8.2.tar.gz
	#@cd lib/readline-8.2 && ./configure --prefix=${PWD}/lib/readline
	#@cd lib/readline-8.2 && make install
	#@$(RM) lib/readline-8.2
	@echo "****   readline ok!    ****"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/lib/readline/include/

$(NAME)	:	$(LIBFT) $(OBJ_DIR) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) -lreadline -L${PWD}/lib/readline/lib  -I${PWD}/lib/readline/include/ -o $(NAME)
	@echo "****   minishell ok!    ****"

clean:
	make clean -C lib/libft
	$(RM) $(OBJ_DIR)

 fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	#$(RM) $(RDLINE)

re:	fclean all

.PHONY: all clean fclean re
