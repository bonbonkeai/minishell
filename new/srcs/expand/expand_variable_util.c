/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:46:44 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:46:45 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_illegal_dollar(const char *input, t_expansion *exp)
{
    if (!append_char(exp, '$'))
        return (0);
    if (input[exp->i])
    {
        if (!append_char(exp, input[exp->i]))
            return (0);
        exp->i++;
    }
    return (1);
}

int	handle_braces(t_expansion *exp, t_env *lst_env)
{
	int		start;
	int		end;

	start = ++exp->i;
	while (exp->str[exp->i] && exp->str[exp->i] != '}')
		exp->i++;
	end = exp->i;
	if (exp->str[exp->i] == '}')
		exp->i++;
    else
    {    
        return (1);
    }
	if (end > start)
	{
		exp->var_name = ft_substr(exp->str, start, end - start);
		if (!exp->var_name)
			return (0);
		return (handle_env_var(exp, lst_env));
	}
	return (1);
}

char *extract_var_name(const char *input, int start, int *matched_len)
{
    int l;

    l = 0;
    if (!ft_isalpha(input[start]) && input[start] != '_')
    {
        *matched_len = 0;
        return (NULL);
    }
    while (ft_isalnum(input[start + l]) || input[start + l] == '_')
        l++;
    *matched_len = l;
    return (ft_substr(input, start, l));
}

int append_str_to_buffer(t_expansion *exp, const char *str)
{
    int i;
	
	i = 0;
    while (str[i])
    {
        if (!append_char(exp, str[i]))
            return (0);
        i++;
    }
    return (1);
}

t_suffix_type get_suffix_type(char c)
{
    if (c == '(' || c == ')' || c == '`')
        return (SUFFIX_SYNTAX_ERROR);
    else if (c == '!')
        return (SUFFIX_HISTORY);
    else if (c == '&')
        return (SUFFIX_BACKGROUND);
    else if (c == ';')
        return (SUFFIX_SEMICOLON);
    else
        return (SUFFIX_OK);
}
