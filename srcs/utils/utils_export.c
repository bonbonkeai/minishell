/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:56:20 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/02 20:01:50 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	if_plus_eq(char *arg, char **key, char **value, int *append)
{
	char	*plus_eq;

	plus_eq = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (plus_eq)
	{
		*append = 1;
		*key = ft_strndup(arg, plus_eq - arg);
		*value = ft_strdup(plus_eq + 2);
		if (!*key || !*value)
		{
			free(*key);
			free(*value);
			*key = NULL;
			*value = NULL;
			return (-1);
		}
		return (1);
	}
	return (0);
}

void	split_var_asin(char *arg, char **key, char **value, int *ap)
{
	char	*eq;

	if (if_plus_eq(arg, key, value, ap) == 0)
	{
		eq = ft_strchr(arg, '=');
		if (eq)
		{
			*ap = 0;
			*key = ft_strndup(arg, eq - arg);
			*value = ft_strdup(eq + 1);
		}
		else
		{
			*key = ft_strdup(arg);
			*value = ft_strdup("");
		}
	}
	if (!*key || !*value)
	{
		free(*key);
		free(*value);
		*key = NULL;
		*value = NULL;
	}
}
