/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:41:23 by jdu               #+#    #+#             */
/*   Updated: 2024/12/06 16:41:25 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calcu_len(long num, char *base_to)
{
	int	len;

	len = 0;
	if (num < 0)
	{
		num = -num;
		len += len + 1;
	}
	else if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= ft_strlen(base_to);
		len++;
	}
	return (len);
}

char	*ft_result(long num, char *base_to)
{
	int		len;
	char	*result;

	len = calcu_len(num, base_to);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (num < 0)
	{
		num = -num;
		result[0] = '-';
	}
	else if (num == 0)
	{
		result[0] = base_to[0];
		result[1] = '\0';
	}
	while (num > 0)
	{
		result[--len] = base_to[num % ft_strlen(base_to)];
		num /= ft_strlen(base_to);
	}
	return (result);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	long	num;
	char	*result;

	if (!ft_is_base(base_from, 0, 0) || !ft_is_base(base_to, 0, 0))
		return (NULL);
	num = ft_deci(nbr, base_from);
	result = ft_result(num, base_to);
	return (result);
}
