/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:46:33 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:46:35 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void handle_single_quote(t_expansion *exp)
// {
//     exp->i++;
//     while (exp->str[exp->i] && exp->str[exp->i] != '\'')
//         append_char(exp, exp->str[exp->i++]);
//     if (exp->str[exp->i] == '\'')
//         exp->i++;
// }
void handle_single_quote(t_expansion *exp)
{
    exp->i++;
    exp->in_squote = 1;
    while (exp->str[exp->i] && exp->str[exp->i] != '\'')
        append_char(exp, exp->str[exp->i++]);
    if (exp->str[exp->i] == '\'')
        exp->i++;
    exp->in_squote = 0;
}

// void handle_double_quote(t_expansion *exp, t_env *env)
// {
//     exp->i++;
//     while (exp->str[exp->i] && exp->str[exp->i] != '\"')
//     {
//         if (exp->str[exp->i] == '$')
//         {
//             if (!handle_dollar(exp->str, exp, env))
//                 return;
//         }
//         else
//         {
//             if (!append_char(exp, exp->str[exp->i]))
//                 return;
//             exp->i++;
//         }
//         // if (exp->str[exp->i] == '$' && valid_exp(exp->str[exp->i + 1]))
//         // {
//         //     if (!handle_dollar(exp->str, exp, env))
//         //         return ;
//         // }
//         // else
//         //     append_char(exp, exp->str[exp->i++]);
//     }
//     if (exp->str[exp->i] == '\"')
//         exp->i++;
// }

void handle_double_quote(t_expansion *exp, t_env *env)
{
    exp->i++;
    exp->in_dquote = 1;
    while (exp->str[exp->i] && exp->str[exp->i] != '\"')
    {
        if (exp->str[exp->i] == '$')
        {
            if (!handle_dollar(exp->str, exp, env))
                return;
        }
        else
        {
            if (!append_char(exp, exp->str[exp->i]))
                return;
            exp->i++;
        }
    }
    if (exp->str[exp->i] == '\"')
        exp->i++;
    exp->in_dquote = 0;
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

// int handle_exit_status(t_expansion *exp, int status)
// {
//     exp->i++;
//     exp->exit_status = ft_itoa(status);
//     if (!exp->exit_status || !append_str(exp))
//         return (0);
//     return (1);
// }
int handle_exit_status(t_expansion *exp)
{
    char *exit_code_str;

    exit_code_str = ft_itoa(exp->status);
    if (!exit_code_str)
        return (0);
    if (!append_str_to_buffer(exp, exit_code_str))
    {
        free(exit_code_str);
        return (0);
    }
    free(exit_code_str);
    return (1);
}

