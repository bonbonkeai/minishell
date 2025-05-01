/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:24:21 by jdu               #+#    #+#             */
/*   Updated: 2024/11/20 15:28:17 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (!dest && !src)
		return (dest);
	d = dest;
	s = src;
	while (n--)
		*d++ = *s++;
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
	char src[] = "Hello, my world!";
	char dest[30];
	
	ft_memcpy(dest, src, 16);
	dest[16] = '\0';
	printf("%s\n", dest);
	return (0);
}*/	
