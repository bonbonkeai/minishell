#include "libft.h"

char *ft_strjoinchr(char *s, char c)
{
    size_t len;
    char *new;
    
    len = ft_strlen(s);
    new = malloc(len + 2);
    if (!new)
        return (NULL);
    ft_strlcpy(new, s, len + 1);
    new[len] = c;
    new[len + 1] = '\0';
    return (new);
}