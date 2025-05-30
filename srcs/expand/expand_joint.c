#include "minishell.h"

char *expand_buffer(char *old_buffer, int *size)
{
    int new_size;
    char *new_buffer;

    new_size = (*size) * 2;
    new_buffer = (char *)malloc(sizeof(char) * new_size);
    if (!new_buffer)
    {
        free(old_buffer);
        return (NULL);
    }
    ft_memcpy(new_buffer, old_buffer, *size);
    free(old_buffer);
    *size = new_size;
    return (new_buffer);
}

int append_str(t_expansion *exp)
{
    int str_len;

    str_len = ft_strlen(exp->exit_status);
    while (exp->len + str_len >= exp->size)
    {
        exp->result = expand_buffer(exp->result, &exp->size);
        if (!exp->result)
            return (free(exp->exit_status), 0);
    }
    ft_strlcpy(exp->result + exp->len, exp->exit_status, exp->size - exp->len);
    exp->len += str_len;
    free(exp->exit_status);
    exp->exit_status = NULL;
    return (1);
}

int append_env(t_expansion *exp)
{
    int str_len;

    str_len = ft_strlen(exp->env_val);
    while (exp->len + str_len >= exp->size)
    {
        exp->result = expand_buffer(exp->result, &exp->size);
        if (!exp->result)
            return (free(exp->env_val), 0);
    }
    ft_strlcpy(exp->result + exp->len, exp->env_val, exp->size - exp->len);
    exp->len += str_len;
    free(exp->env_val);
    exp->env_val = NULL;
    return (1);
}

