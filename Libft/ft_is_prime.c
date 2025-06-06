/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:40:59 by jdu               #+#    #+#             */
/*   Updated: 2024/12/06 16:41:01 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_prime(int nb)
{
	int	num;

	num = 3;
	if (nb <= 1 || (nb % 2 == 0 && nb != 2))
		return (0);
	else if (nb == 2)
		return (1);
	while (num <= nb / num)
	{
		if (nb % num == 0)
			return (0);
		num += 2;
	}
	return (1);
}
