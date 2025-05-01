/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:30:22 by jdu               #+#    #+#             */
/*   Updated: 2024/11/08 17:43:06 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = s1;
	p2 = s2;
	while (n--)
	{
		if (*p1 != *p2)
		{
			return (*p1 - *p2);
		}
		p1++;
		p2++;
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	char *s1 = "hello wolrd";
	char *s2 = "hello my world";
	char *s3 = "hello world!!!";

	int r1 = ft_memcmp(s1, s2, sizeof(s1));
	printf("%d\n", r1);
	int r2 = ft_memcmp(s1, s3, sizeof(s1));
	printf("%d\n", r2);
	return (0);
}*/
