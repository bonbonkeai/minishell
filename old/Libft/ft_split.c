/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:26:37 by jdu               #+#    #+#             */
/*   Updated: 2024/11/20 15:14:42 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_words(char const *str, char c)
{
	size_t	i;
	size_t	count;
	size_t	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		else if (str[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static char	*ft_strndup3(char const *str, size_t n)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = malloc(n + 1);
	if (!dest)
		return (NULL);
	while (str[i] && i < n)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_free(char **result, size_t i)
{
	while (i > 0)
		free(result[--i]);
	free(result);
}

static char	**ft_result(char const *s, char c, char **result)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		len = 0;
		while (s[len] != '\0' && s[len] != c)
			len++;
		if (len > 0)
		{
			result[i] = ft_strndup3(s, len);
			if (!result[i])
				return (ft_free(result, i), NULL);
			i++;
		}
		s += len;
	}
	return (result[i] = NULL, result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (!ft_result(s, c, result))
		return (NULL);
	return (result);
}
