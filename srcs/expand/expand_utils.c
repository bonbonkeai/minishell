#include "minishell.h"

void handle_single_quote(t_expansion *exp)
{
    exp->i++;
    while (exp->str[exp->i] && exp->str[exp->i] != '\'')
        append_char(exp, exp->str[exp->i++]);
    if (exp->str[exp->i] == '\'')
        exp->i++;
}

void handle_double_quote(t_expansion *exp, t_env *env, int status)
{
    exp->i++;
    while (exp->str[exp->i] && exp->str[exp->i] != '\"')
    {
        if (exp->str[exp->i] == '$' && valid_exp(exp->str[exp->i + 1]))
        {
            if (!handle_dollar(exp->str, exp, env, status))
                return ;
        }
        else
            append_char(exp, exp->str[exp->i++]);
    }
    if (exp->str[exp->i] == '\"')
        exp->i++;
}

int append_char(t_expansion *exp, char c)
{
    if (exp->len + 1 >= exp->size)
    {
        if (!handle_buffer(exp))
            return (0);
    }
    exp->buf[exp->len++] = c;
    exp->buf[exp->len] = '\0';
    return (1);
}

int valid_exp(int c)
{
    if (c == '?' || c == '{' || ft_isalnum(c) || c == '_')
        return (1);
    return (0);
}

int handle_buffer(t_expansion *exp)
{
    char *new_buf;
    int new_size;

    new_size = exp->size * 2;
    new_buf = malloc(new_size);
    if (!new_buf)
        return (0);
    ft_memcpy(new_buf, exp->buf, exp->len);
    free(exp->buf);
    exp->buf = new_buf;
    exp->size = new_size;
    return (1);
}

int handle_exit_status(t_expansion *exp, int status)
{
    exp->i++;
    exp->exit_status = ft_itoa(status);
    if (!exp->exit_status || !append_str(exp))
        return (0);
    return (1);
}







// char *expand_line(char *input, t_env *env, int status)
// {
//     t_expansion exp;

//     if (!input)
//         return (NULL);
//     if (!init_expand(&exp))
//         return (free(input), NULL);
//     exp.str = input;
//     while (exp.str[exp.i])
//     {
//         if (exp.str[exp.i] == '\'' && !exp.in_dquote)
//             handle_single_quote(&exp);
//         else if (exp.str[exp.i] == '\"' && !exp.in_squote)
//             handle_double_quote(&exp, env, status);
//         // else if (exp.str[exp.i] == '$' && valid_exp(exp.str[exp.i + 1]) && !exp.in_squote)
//         else if (exp.str[exp.i] == '$' && !exp.in_squote)
//         {
//             if (!handle_dollar(exp.str, &exp, env, status))
//                 return (free(input), free(exp.buf), NULL);
//         }
//         else
//         {
//             if (!append_char(&exp, exp.str[exp.i]))
//                 return (free(input), free(exp.buf), NULL);
//             exp.i++;
//         }
//     }
//     exp.buf[exp.len] = '\0';
//     free(input);
//     return (exp.buf);
// }

int has_quote(char *str)
{
    int i;

    if (!str)
        return (0);
    i = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
            return (1);
        i++;
    }
    return (0);
}


