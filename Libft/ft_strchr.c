/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:00:54 by jdu               #+#    #+#             */
/*   Updated: 2024/11/20 15:24:43 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	char *s = "hello, world";
	char *r;

	r = ft_strchr(s, 'o');
	if (r != NULL)
		printf("trouver, %ld\n", r - s);
	else 
		printf("non trouver\n");
	return (0);
}*/
