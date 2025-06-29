/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:47:07 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:47:08 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int has_quote(const char *str)
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

char *remove_quotes(const char *str)
{
    size_t len;
    
    len = ft_strlen(str);
    if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"') || 
                     (str[0] == '\'' && str[len - 1] == '\'')))
    {
        return ft_substr(str, 1, len - 2);
    }
    return ft_strdup(str);
}

int valid_exp(int c)
{
    if (c == '?' || c == '{' || ft_isalnum(c) || c == '_')
        return (1);
    return (0);
}