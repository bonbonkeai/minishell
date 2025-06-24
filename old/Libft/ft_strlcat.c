/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:00:17 by jdu               #+#    #+#             */
/*   Updated: 2024/09/23 20:31:23 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_dest;
	size_t	len_src;

	i = 0;
	len_src = ft_strlen(src);
	len_dest = ft_strlen(dest);
	if (dstsize <= len_dest)
		return (dstsize + len_src);
	while (src[i] != '\0' && (len_dest + i) < (dstsize - 1))
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	if ((len_dest + i) < dstsize)
		dest[len_dest + i] = '\0';
	return (len_dest + len_src);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	s1[27] = "abcdefghigklmn";
	char	s2[] = "opqrstuvwxwz";
	char	s3[8] = "0123";
	char	s4[] = "456789";

	int	r1 = ft_strlcat(s1, s2, 27);
	int	r2 = ft_strlcat(s3, s4, 8);
	printf("%s\n%s\n", s1, s3);
	printf("%d, %d\n", r1, r2);

	//char    s5[27] = "abcdefghigklmn";
        //char    s6[] = "opqrstuvwxwz";
        //char    s7[8] = "0123";
        //char    s8[] = "456789";

        //int     r3 = strlcat(s5, s6, 27);
        //int     r4 = strlcat(s7, s8, 8);
        //printf("%s\n%s\n", s5, s7);
        //printf("%d, %d\n", r3, r4);
	return (0);
}*/
