/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:13:13 by jdu               #+#    #+#             */
/*   Updated: 2025/01/30 17:18:10 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <fcntl.h>
# include <limits.h>

# define FD_MAX 1024

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif

char	*get_next_line(int fd);
void	*ft_memcpy(void *dest, const void *src, size_t n);
//char	*ft_strjoin(char const *s1, char const *s2);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_clist
{
	char	content;
	void	*next;
}		t_clist;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(char const *str);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *src);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *p, size_t old_size, size_t new_size);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_strcpy(char *dest, const char *src);

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
int		ft_lstsize(t_list *lst);

int		ft_printf(const char *type, ...);
int		ft_print_c(int c);
int		ft_print_s(const char *s);
int		ft_print_p(void *p);
int		ft_print_nbr(int n);
int		ft_print_u(unsigned int n);
int		ft_print_x(unsigned int n);
int		ft_print_mx(unsigned int n);
int		ft_is_type(char c);
int		ft_pour_p(uintptr_t n);

int		ft_fprintf(int fd, const char *type, ...);
int		ft_pourp(uintptr_t n, int fd);
int		ft_printc(int c, int fd);
int		ft_prints(const char *s, int fd);
int		ft_printp(void *p, int fd);
int		ft_printnbr(int n, int fd);
int		ft_printu(unsigned int n, int fd);
int		ft_printx(unsigned int n, int fd);
int		ft_printmx(unsigned int n, int fd);
int		ft_is_ftype(char c);

int		ft_atoi_base(char *str, char *base);
char	*ft_convert_base(char *nbr, char *base_from, char *base_to);
int		ft_is_base(char *base, size_t i, size_t j);
long	ft_deci(char *str, char *base_from);
int		ft_is_prime(int nb);
void	ft_putchar(char c);
void	ft_putnbr_base(int nbr, char *base);
void	ft_putnbr(int nb);
void	ft_putstr(char *str);
void	ft_rev_int_tab(int *tab, int size);
void	ft_sort_int_tab(int *tab, int size);
char	*ft_strcat(char *dest, char *src);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strncat(char *dest, char *src, unsigned int nb);
char	*ft_strndup(const char *src, size_t n);
char	*ft_strstr(char *str, char *to_find);
void	ft_swap(int *a, int *b);
int		ft_abs(int num);
void	ft_lstclear_gnl(t_clist **lst);
void	ft_lstadd_back_gnl(t_clist **lst, t_clist *new);
t_clist	*copy_tolist(t_clist **lst, const char *src, int size);
int		lst_find_nl(t_clist *lst);
int		lst_count_nlorend(t_clist *lst);

char *ft_strjoinchr(char *s, char c);
int	ft_isspace(char c);

#endif
