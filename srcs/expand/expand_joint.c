#include "minishell.h"

int append_str(t_expansion *exp)
{
    int str_len;

    str_len = ft_strlen(exp->exit_status);
    while (exp->len + str_len >= exp->size)
    {
        exp->buf = expand_buffer(exp->buf, &exp->size);
        if (!exp->buf)
            return (free(exp->exit_status), 0);
    }
    ft_strlcpy(exp->buf + exp->len, exp->exit_status, exp->size - exp->len);
    exp->len += str_len;
    free(exp->exit_status);
    exp->exit_status = NULL;
    return (1);
}

int append_env(t_expansion *exp)
{
    int str_len;

    if (!exp->env_val)
        return (1);
    str_len = ft_strlen(exp->env_val);
    while (exp->len + str_len >= exp->size)
    {
        exp->buf = expand_buffer(exp->buf, &exp->size);
        if (!exp->buf)
            return (0);
    }
    ft_strlcpy(exp->buf + exp->len, exp->env_val, exp->size - exp->len);
    exp->len += str_len;
    exp->env_val = NULL;
    return (1);
}

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

int handle_env_var(t_expansion *exp, t_env *lst_env)
{
    exp->env_val = get_env_value(lst_env, exp->var_name);
    if (!exp->env_val || !append_env(exp))
        return (0);
    return (1);
}