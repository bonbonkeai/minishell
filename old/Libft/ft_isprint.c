/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:41:15 by jdu               #+#    #+#             */
/*   Updated: 2024/11/08 15:46:29 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
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
		res = ft_isprint(atoi(av[1]));
		printf("%d\n", res);
	}
	return (0);
}*/
