/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:11:39 by jdu               #+#    #+#             */
/*   Updated: 2024/11/20 15:25:03 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = 0;
	while (*s != '\0')
	{
		if (*s == (char)c)
			last = s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)last);
}
/*
#include <stdio.h>
int	main(void)
{
	char *s = "hello, world";
	char ch = 'o';
	char *r;

	r = ft_strrchr(s, ch);
	if (r != NULL)
		printf("trouver %c, %ld\n", ch, r - s);
	else
		printf("non trouver\n");
	r = ft_strrchr(s, '\0');
	if (r)
		printf("trouver '\\0', %ld\n", r - s);
	return (0);
}*/
