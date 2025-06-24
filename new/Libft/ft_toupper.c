/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:51:09 by jdu               #+#    #+#             */
/*   Updated: 2024/11/08 16:56:55 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	else
		return (c);
}
/*
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	int res;

	if (ac > 1)
	{
		res = ft_toupper(atoi(av[1]));
		printf("%d\n", res);
	}
	return (0);
}*/
