CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
NAME_BONUS = 
LIBFT = ./Libft/libft.a

SRCS = ./srcs/error_check.c \
	

SRCS_BONUS = ./srcs_bonus/checker_bonus.c \
	

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)
bonus: $(NAME_BONUS)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	
$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBFT)

$(LIBFT):
			make -C ./Libft

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	make clean -C ./Libft

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	make fclean -C ./Libft

re: fclean all

rebonus: fclean bonus 

.PHONY: all clean fclean re bonus rebonus