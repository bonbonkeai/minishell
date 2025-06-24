CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRCS = ft_isalpha.c \
       ft_isdigit.c \
       ft_isalnum.c \
       ft_isascii.c \
       ft_isprint.c \
       ft_strlen.c \
       ft_memset.c \
       ft_bzero.c \
       ft_memcpy.c \
       ft_memmove.c \
       ft_strlcpy.c \
       ft_strlcat.c \
       ft_toupper.c \
       ft_tolower.c \
       ft_strchr.c \
       ft_strrchr.c \
       ft_strncmp.c \
       ft_memchr.c \
       ft_memcmp.c \
       ft_strnstr.c \
       ft_atoi.c \
       ft_calloc.c \
       ft_strdup.c \
       ft_substr.c \
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
       ft_realloc.c \
       ft_printf.c \
       ft_is_type.c \
       ft_types.c \
       get_next_line.c \
       get_next_line_utils.c \
       gnl_djy/gnl.c \
       gnl_djy/gnl_utils.c \
       gnl_djy/get_next_line_bonus.c \
       gnl_djy/get_next_line_utils_bonus.c \
       ft_fprintf.c \
       ft_is_ftype.c \
       ftypes.c \
       ft_putchar.c \
       ft_putstr.c \
       ft_putnbr.c \
       ft_strndup.c \
       ft_swap.c \
       ft_rev_int_tab.c \
       ft_sort_int_tab.c \
       ft_strcmp.c \
       ft_strcat.c \
       ft_strncat.c \
       ft_strstr.c \
       ft_putnbr_base.c \
       ft_atoi_base.c \
       ft_is_prime.c \
       ft_convert_base.c \
       ft_convert_base2.c \
       ft_strcpy.c \
       ft_abs.c \
       ft_isspace.c \
       ft_strjoinchr.c \

       
BONUS = ft_lstnew_bonus.c \
       ft_lstadd_front_bonus.c \
       ft_lstsize_bonus.c \
       ft_lstlast_bonus.c \
       ft_lstadd_back_bonus.c \
       ft_lstdelone_bonus.c \
       ft_lstclear_bonus.c \
       ft_lstiter_bonus.c \
       ft_lstmap_bonus.c

OBJS_BONUS = $(BONUS:.c=.o)
OBJS = $(SRCS:.c=.o)
INCDIR = .

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCDIR)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(OBJS) $(OBJS_BONUS)
	ar -rc $(NAME) $(OBJS) $(OBJS_BONUS)
	ranlib $(NAME)

rebonus: fclean bonus 

.PHONY: all clean fclean re bonus rebonus
