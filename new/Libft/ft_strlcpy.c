/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:24:51 by jdu               #+#    #+#             */
/*   Updated: 2024/09/22 12:35:54 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (src[len] != '\0')
		len++;
	if (dstsize == 0)
		return (len);
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}
/*strlcpy -> assurer la size de dest peut copier, return->lenth of src*/
/*
#include <stdio.h>
int	main(void)
{
	char	s1[] = "hahahahahahahaha";
	char	s2[] = "xixixixixixo";
	char	s3[10];
	char	s4[5];

	int	r1 = ft_strlcpy(s3, s1, 10);
	int	r2 = ft_strlcpy(s4, s2, 5);
	printf("%s\n%s\n", s3, s4);
	printf("%d, %d\n", r1, r2);
	return (0);
}*/
