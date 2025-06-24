/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:08:54 by jdu               #+#    #+#             */
/*   Updated: 2024/11/08 15:22:18 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
		return (1);
	else
		return (0);
}
/*
#include <stdlib.h>
#include <stdio.h>
int	main(int ac, char **av)
{
	int	res;

	if (ac > 1)
	{
		res = ft_isalpha(atoi(av[1]));
		printf("%d\n", res);
	}
	return (0);
}*/
