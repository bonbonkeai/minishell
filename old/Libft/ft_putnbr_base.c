/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:40:34 by jdu               #+#    #+#             */
/*   Updated: 2024/12/06 17:18:58 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_convert_base2(char *base, char *result, long nbr)
{	
	size_t	len;
	long	term;

	len = 0;
	term = nbr;
	if (term == 0)
	{
		result[len++] = base[0];
		result[len] = '\0';
		return ;
	}
	len = 0;
	while (term > 0)
	{
		term /= ft_strlen(base);
		len++;
	}
	result[len] = '\0';
	while (nbr > 0)
	{
		result[--len] = base[nbr % ft_strlen(base)];
		nbr /= ft_strlen(base);
	}
}

void	ft_putnbr_base(int nbr, char *base)
{
	size_t		i;
	long		term;
	char		result[34];

	i = 0;
	term = nbr;
	if (ft_is_base(base, 0, 0) == 0)
		return ;
	if (nbr < 0)
	{
		ft_putchar('-');
		term = -term;
	}
	ft_convert_base2(base, result, term);
	while (result[i])
	{
		ft_putchar(result[i]);
		i++;
	}
}
