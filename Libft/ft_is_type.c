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

int	ft_is_type(char c)
{
	if (c == 'c' || c == 's' || c == 'd' || c == 'i' || c == 'p' || \
		c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	ft_pour_p(uintptr_t n)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		count += ft_pour_p(n / 16);
	count += ft_print_c(base[n % 16]);
	return (count);
}
