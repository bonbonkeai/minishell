/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:46:44 by jdu               #+#    #+#             */
/*   Updated: 2025/07/02 15:10:49 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_and_handle_suffix(const char *input, \
		t_expansion *exp, int matched_len)
{
	t_suffix_type	type;
	char			next;

	next = input[exp->i + matched_len];
	type = get_suffix_type(next);
	if (type == SUFFIX_OK)
		return (1);
	exp->illegal_type = type;
	if (exp->error_char)
		free(exp->error_char);
	exp->error_char = ft_substr(input, exp->i + matched_len, 1);
	return (0);
}

int	expand_and_append_value(t_expansion *exp, \
		const char *value, int matched_len)
{
	if (value && !append_str_to_buffer(exp, value))
		return (0);
	exp->i += matched_len;
	return (1);
}

static int	append_and_step(t_expansion *exp, char *input)
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

static int	handle_key_expansion(char *input, t_expansion *exp, \
		t_env *lst_env)
{
	int		matched_len;
	char	*key;
	char	*value;
	int		r;

	matched_len = 0;
	key = extract_var_name(input, exp->i, &matched_len);
	if (!key)
		return (append_and_step(exp, input));
	value = get_env_value(lst_env, key);
	if (!check_and_handle_suffix(input, exp, matched_len))
		return (free(key), 0);
	r = expand_and_append_value(exp, value, matched_len);
	return (free(key), r);
}

int	handle_dollar(char *input, t_expansion *exp, t_env *lst_env)
{
	int	r;

	exp->i++;
	if (input[exp->i] == '?')
		return (handle_question_mark(exp));
	if (handle_digit_after_dollar(input, exp))
		return (1);
	r = handle_illegal_or_braces(input, exp, lst_env);
	if (r != -1)
		return (r);
	return (handle_key_expansion(input, exp, lst_env));
}
