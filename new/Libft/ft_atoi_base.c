/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:40:47 by jdu               #+#    #+#             */
/*   Updated: 2024/12/06 17:19:54 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_index(char c, char *base)
{
	size_t	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	size_t	i;
	int		sign;
	int		result;

	i = 0;
	sign = 1;
	result = 0;
	if (ft_is_base(base, 0, 0) == 0)
		return (0);
	while (str[i] == ' ' || (str[i] <= 13 && str[i] >= 9))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] != '\0' && get_index(str[i], base) != -1)
	{
		result = result * ft_strlen(base) + get_index(str[i], base);
		i++;
	}
	return (result * sign);
}
