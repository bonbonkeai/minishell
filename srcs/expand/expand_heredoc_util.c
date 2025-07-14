/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:46:34 by jdu               #+#    #+#             */
/*   Updated: 2025/07/09 14:25:28 by jdu              ###   ########.fr       */
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

char	*strip_outer_quotes(const char *s)
{
	char	*stripped;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (len >= 2 && ((s[0] == '"' && s[len - 1] == '"') || \
		(s[0] == '\'' && s[len - 1] == '\'')))
	{
		stripped = ft_substr(s, 1, len - 2);
		if (!stripped)
			return (NULL);
		return (stripped);
	}
	return (ft_strdup(s));
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
		lim = strip_outer_quotes(target);
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
