CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
NAME = minishell
NAME_BONUS = 
LIBFT = ./Libft/libft.a

SRCS = ./srcs/initialization/init_cmd.c \
		./srcs/initialization/init_env.c \
		./srcs/initialization/init_expan.c \
		./srcs/initialization/init_path.c \
		./srcs/initialization/init_shell.c \
		./srcs/signal/pas_sur.c \
		./srcs/lexer/lexer.c \
		./srcs/tokenizer/tokenizer.c \
		./srcs/redirection/red.c \
		./srcs/redirection/red_utils.c \
		./srcs/redirection/handle_red.c \
		./srcs/redirection/handle_heredoc.c \
		./srcs/parser/parser.c \
		./srcs/prompt/prompt_home.c \
		./srcs/prompt/prompt_build.c \
		./srcs/minishell.c \
		./srcs/executor/executor.c \
		./srcs/executor/exec_simple.c \
		./srcs/executor/exec_utils.c \
		./srcs/executor/exec_handle_pipes.c \
		./srcs/executor/exec_pipe.c \
		./srcs/utils/utils_cmd.c \
		./srcs/utils/utils_redir.c \
		./srcs/utils/utils_setpath.c 
		# ./srcs/expand/expand_joint.c \
		# ./srcs/expand/expand_variable.c \
		# ./srcs/expand/expander.c \
		# ./srcs/expand_heredoc.c \
		# ./srcs/expand_heredoc_utils.c \
		# ./srcs/executor/ \
		# ./srcs/builtin/ 
		
	

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