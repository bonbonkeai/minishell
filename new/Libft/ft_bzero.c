/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:04:15 by jdu               #+#    #+#             */
/*   Updated: 2024/11/08 16:12:55 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
/*
#include <stdio.h>
int	main(void)
{
	char	buff[10];
	int	i;

	ft_bzero(buff, sizeof(buff));
	i = 0;
	while (i < 10)
	{
		printf("%d\n", buff[i]);
		i++;
	}
	return (0);
}*/
