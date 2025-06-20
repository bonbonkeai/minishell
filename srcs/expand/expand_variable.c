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

int handle_illegal_dollar(char *input, t_expansion *exp)
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

int handle_dollar(char *input, t_expansion *exp, t_env *lst_env)
{
    char *key;
    char *value;
    int matched_len;
    char next;
    t_suffix_type type;

    key = NULL;
    value = NULL;
    matched_len = 0;
    exp->i++;
    if (input[exp->i] == '?')
    {
        exp->i++;
        if (!handle_exit_status(exp))
            return (0);
        return (1);
    }
    if (ft_isdigit(input[exp->i]))
    {
        exp->i++;
        return (1);
    }
    if (input[exp->i] == '{')
        return (handle_braces(exp, lst_env));
    if (!ft_isalpha(input[exp->i]) && input[exp->i] != '_' && input[exp->i] != '\0')
        return (handle_illegal_dollar(input, exp));
    key = extract_var_name(input, exp->i, &matched_len);
    if (key)
	{
		value = get_env_value(lst_env, key);
		next = input[exp->i + matched_len];
		type = get_suffix_type(next);
        if (type != SUFFIX_OK)
		{
			exp->illegal_type = type;
            if (exp->error_char)
		        free(exp->error_char);
            exp->error_char = ft_substr(input, exp->i + matched_len, 1);
			free(key);
			return (0);
		}
		if (value && !append_str_to_buffer(exp, value))
		{
			free(key);
			return (0);
		}
		exp->i += matched_len;
		free(key);
		return (1);
	}
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
    return ft_substr(input, start, l);
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
    if (c == '|')
        return (SUFFIX_PIPE);
    else if (c == '>' || c == '<')
        return (SUFFIX_REDIR);
    else if (c == '(' || c == ')' || c == '`')
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

// int	handle_variable(char *input, t_expansion *exp, t_env *lst_env)
// {
// 	exp->k = 0;
// 	if (!ft_isalpha(input[exp->i]) && input[exp->i] != '_')
// 		return (1);
// 	while (ft_isalnum(input[exp->i]) || input[exp->i] == '_')
// 	{
// 		if (exp->k >= MAX_VAR_NAME_LEN - 1)
// 			break ;
// 		exp->var_name[exp->k++] = input[exp->i++];
// 	}
// 	exp->var_name[exp->k] = '\0';
// 	if (exp->k == 0)
// 		return (1);
// 	if (!handle_env_var(exp, lst_env))
// 		return (0);
// 	return (1);
// }
