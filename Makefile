CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
NAME = minishell
NAME_BONUS = 
LIBFT = ./Libft/libft.a

SRCS = ./srcs/initialization/init_cmd.c \
		./srcs/initialization/init_env.c \
		./srcs/initialization/init_path.c \
		./srcs/initialization/init_shell.c \
		./srcs/initialization/init_expan.c \
		./srcs/lexer/lexer.c \
		./srcs/tokenizer/tokenizer.c \
		./srcs/redirection/red.c \
		./srcs/redirection/red_utils.c \
		./srcs/parser/parser.c \
		./srcs/minishell.c \
		./srcs/expand/expand.c \
		./srcs/expand/expand_joint.c \
		./srcs/expand/expand_variable.c \
		./srcs/expand/expand_utils.c \
		# ./srcs/expand/expand_heredoc.c \
		# ./srcs/expand/expand_heredoc_utils.c \
		# ./srcs/executor/ \
		# ./scrs/builtin/ \
		# ./scrs/signal/ \
		# ./scrs/promt/promt.c \
		
	

SRCS_BONUS = ./srcs_bonus/ \
	

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)
bonus: $(NAME_BONUS)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBFT) -lreadline

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