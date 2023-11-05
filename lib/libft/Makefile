SRCS	=	ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \

SRCS_B	=	ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c \

NAME	=	libft.a
CC		=	gcc
INC		=	libft.h
CFLAGS	=	-Wall -Wextra -Werror
AR		=	ar -rcs
RM		=	rm -rf

OBJ_DIR =	objs
OBJ		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJS_B	=	$(SRCS_B:%_bonus.c=$(OBJ_DIR)/%_bonus.o)

all : $(NAME)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	:	$(OBJ_DIR) $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "Libft ok!"

clean :
	@$(RM) $(OBJ_DIR)

fclean : clean
	@$(RM) $(NAME)

bonus : $(OBJ_DIR) $(OBJ) $(OBJS_B)
	@$(AR) $(NAME) $(OBJ) $(OBJS_B)
	@echo "Libft bonus ok!"

re : fclean all

rebonus : fclean bonus

.PHONY: all clean fclean