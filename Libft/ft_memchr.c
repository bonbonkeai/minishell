/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:22:27 by jdu               #+#    #+#             */
/*   Updated: 2024/11/08 17:28:36 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;

	p = s;
	while (n--)
	{
		if (*p == (unsigned char)c)
			return ((void *)p);
		p++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char *s = "hello, world";
	char ch = 'o';
	char *r;

	r = ft_memchr(s, ch, sizeof(s));
	if (r != NULL)
		printf("trouver %c, %ld\n", ch, r - s);
	else
		printf("non trouver\n");
	return (0);
}*/
