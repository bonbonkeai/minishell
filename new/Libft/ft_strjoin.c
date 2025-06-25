/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:25:56 by jdu               #+#    #+#             */
/*   Updated: 2024/12/06 14:43:09 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = (char *)malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, len1);
	ft_memcpy(res + len1, s2, len2);
	res[len1 + len2] = '\0';
	return (res);
}
/*char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;

	res = (char *)malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*s1 != '\0')
	{
		res[i] = *s1++;
		i++;
	}
	while (*s2 != '\0')
	{
		res[i] = *s2++;
		i++;
	}
	res[i] = '\0';
	return (res);
}*/
