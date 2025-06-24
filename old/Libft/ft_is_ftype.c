/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:32:45 by jdu               #+#    #+#             */
/*   Updated: 2024/11/22 19:18:59 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_is_ftype(char c)
{
	if (c == 'c' || c == 's' || c == 'd' || c == 'i' || c == 'p' || \
		c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	ft_pourp(uintptr_t n, int fd)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		count += ft_pourp((n / 16), fd);
	count += ft_printc((base[n % 16]), fd);
	return (count);
}
