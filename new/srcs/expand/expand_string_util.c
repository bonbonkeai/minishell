/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:46:02 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:46:04 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *handle_expand_error(t_expansion *exp, t_suffix_type *out_type, char *error_char)
{
	if (out_type)
		*out_type = exp->illegal_type;
	if (error_char)
	{
		if (exp->error_char)
			*error_char = exp->error_char[0];
		else
			*error_char = '\0';
	}
	free_expansion(exp);
	return (NULL);
}

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

int handle_double_quote(t_expansion *exp, t_env *env)
{
    exp->i++;
    exp->in_dquote = 1;
    while (exp->str[exp->i] && exp->str[exp->i] != '\"')
    {
        if (exp->str[exp->i] == '$')
        {
            if (!handle_dollar(exp->str, exp, env))
                return (0);
        }
        else
        {
            if (!append_char(exp, exp->str[exp->i]))
                return (0);
            exp->i++;
        }
    }
    if (exp->str[exp->i] == '\"')
        exp->i++;
    exp->in_dquote = 0;
    return (1);
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

int handle_buffer(t_expansion *exp)
{
    char *new_buf;
    int new_size;

    new_size = exp->size * 2;
    new_buf = malloc(new_size);
    if (!new_buf)
        return (0);
    ft_memcpy(new_buf, exp->buf, exp->len);
    new_buf[exp->len] = '\0';
    free(exp->buf);
    exp->buf = new_buf;
    exp->size = new_size;
    return (1);
}