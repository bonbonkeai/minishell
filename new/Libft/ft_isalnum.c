/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:31:22 by jdu               #+#    #+#             */
/*   Updated: 2024/11/08 15:36:23 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
#include <stdlib.h>

int     main(int ac, char **av)
{
        int     res;

        if (ac > 1)
        {
                res = ft_isalnum(atoi(av[1]));
                printf("%d\n", res);
        }
        return (0);
}*/
