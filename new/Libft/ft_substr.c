/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:26:14 by jdu               #+#    #+#             */
/*   Updated: 2024/11/20 13:26:16 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup2(const char *s, unsigned int start, size_t n)
{
	size_t	i;
	char	*d;

	i = 0;
	d = (char *)malloc(n + 1);
	if (!d)
		return (NULL);
	while (i < n)
	{
		d[i] = s[start + i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	final_len;
	char	*s2;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		final_len = s_len - start;
	else
		final_len = len;
	s2 = ft_strndup2(s, start, final_len);
	if (!s2)
		return (NULL);
	return (s2);
}
/*
#include <stdio.h>
#include <stdlib.h>
int	main(int ac, char **av)
{
	char	*src;
	char	*r;
	unsigned int	s;
	size_t	len;

	src = av[1];
	s = atoi(av[2]);
	len = (size_t)atoi(av[3]);
	if (ac == 4)
	{
		r = ft_substr(src, s, len);
		printf("%s\n", r);
		free(r);
	}
	return (0);
}*/	
