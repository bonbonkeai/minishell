/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:37:21 by jdu               #+#    #+#             */
/*   Updated: 2024/11/08 15:40:17 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
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
		res = ft_isascii(atoi(av[1]));
		printf("%d\n", res);
	}
	return (0);
}*/
