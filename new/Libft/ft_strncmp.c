/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:48:32 by jdu               #+#    #+#             */
/*   Updated: 2024/09/23 20:33:34 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	diff;

	i = 0;
	diff = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] == s2[i])
			i++;
		else
		{
			diff = ((unsigned char)s1[i] - (unsigned char)s2[i]);
			break ;
		}
	}
	return (diff);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char    s1[] = "Hello world, my girl!";
	char    s2[] = "my world!";
	char    s3[] = "Hello world, my girls!";
	char    s4[] = "Hello world, my girl!";
	char    s5[] = " ";
	char    s6[] = "";
	char	s7[] = "Hello";
	char	s8[] = "Hell";
	
	int     r1 = ft_strncmp(s1, s2, 10);
	int     r2 = ft_strncmp(s1, s3, 30);
	int     r3 = ft_strncmp(s1, s4, 5);
	int     r4 = ft_strncmp(s1, s5, 2);
	int     r5 = ft_strncmp(s1, s6, 1);
	int	r11 = ft_strncmp(s7, s8, 4);
	printf("%d, %d, %d, %d, %d, %d\n", r1, r2, r3, r4, r5, r11);

	int     r6 = strncmp(s1, s2, 10);
        int     r7 = strncmp(s1, s3, 30);
        int     r8 = strncmp(s1, s4, 5);
        int     r9 = strncmp(s1, s5, 2);
        int     r10 = strncmp(s1, s6, 1);
	int	r12 = strncmp(s7, s8, 4);
        printf("%d, %d, %d, %d, %d, %d\n", r6, r7, r8, r9, r10, r12);
	return (0);
}*/
