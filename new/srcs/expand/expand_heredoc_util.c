/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:46:34 by jdu               #+#    #+#             */
/*   Updated: 2025/07/02 15:14:09 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_quote(const char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (1);
		str++;
	}
	return (0);
}

char	*merge_quoted_string(const char *limiter)
{
	int		i;
	int		j;
	char	*merged;

	i = 0;
	j = 0;
	if (!limiter)
		return (NULL);
	merged = malloc(sizeof(char) * (ft_strlen(limiter) + 1));
	if (!merged)
		return (NULL);
	while (limiter[i])
	{
		if (!is_quote(limiter[i]))
			merged[j++] = limiter[i];
		i++;
	}
	merged[j] = '\0';
	return (merged);
}

int	valid_exp(int c)
{
	if (c == '?' || c == '{' || ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*get_heredoc_content(char *target, char *lim, t_shell *sh)
{
	char	*res;

	if (!lim)
		return (process_heredoc_content(target, sh));
	else
	{
		res = process_heredoc_content(lim, sh);
		free(lim);
		return (res);
	}
}

char	*set_should_expand(t_shell *sh, char *target)
{
	char	*lim;

	if (has_quote(target))
	{
		sh->should_expand = 0;
		lim = merge_quoted_string(target);
		if (!lim)
			return (NULL);
	}
	else
	{
		sh->should_expand = 1;
		lim = NULL;
	}
	return (lim);
}