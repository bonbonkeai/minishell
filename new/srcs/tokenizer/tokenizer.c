/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:45:29 by jdu               #+#    #+#             */
/*   Updated: 2025/07/02 19:57:47 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_prompt(t_shell *sh, const char *line)
{
	int	i;
	int	skip;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else
		{
			skip = get_operator_token(line, i, &sh->token_list);
			if (skip > 0)
				i += skip;
			else
				i += get_word_token(line, i, sh);
		}
	}
}

void	free_tokens(t_token *tok)
{
	t_token	*tmp;

	if (!tok)
		return ;
	while (tok)
	{
		tmp = tok->next;
		if (tok->content)
			free(tok->content);
		free(tok);
		tok = tmp;
	}
}

int	check_token_syntax(t_token *t)
{
	if (!t)
		return (ft_fprintf(2, "minishell: empty input\n"), 1);
	if (t->type == T_PIPE)
		return (ft_fprintf(2, ERR_PIPE), 1);
	while (t)
	{
		if (t->type == T_PIPE)
		{
			if (!t->next || t->next->type == T_PIPE)
				return (ft_fprintf(2, ERR_DOUBLE_PIPE), 1);
		}
		if (is_red_type(t->type))
		{
			if (!t->next)
				return (ft_fprintf(2, ERR_NEWLINE), 1);
			if (t->next->type != T_WORD)
				return (ft_fprintf(2, ERR_TOKEN, t->next->content), 1);
		}
		t = t->next;
	}
	return (0);
}

int	check_pipe(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (tokens->type == T_PIPE)
		return (1);
	while (tokens)
	{
		if (tokens->type == T_PIPE && (!tokens->next \
		|| tokens->next->type == T_PIPE))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
