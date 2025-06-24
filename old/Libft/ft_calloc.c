/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:59:14 by jdu               #+#    #+#             */
/*   Updated: 2024/11/08 18:11:35 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t	i;

	p = s;
	i = 0;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*p;

	total = nmemb * size;
	p = malloc(total);
	if (p == NULL)
		return (NULL);
	ft_memset(p, 0, total);
	return (p);
}
/*
#include <stdio.h>
int	main(void)
{
	int	*a = (int *)ft_calloc(5, sizeof(int));
	size_t	i = 0;
	
	if (a != NULL)
	{
		while (i < 5)
		{
			printf("a[%zu] = %d\n", i, a[i]);
			i++;
		}
	}
	free(a);
	return (0);
}*/	
