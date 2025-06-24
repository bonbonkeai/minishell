/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:54:49 by jdu               #+#    #+#             */
/*   Updated: 2024/11/20 18:32:09 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_nbr(int n)
{
	int		count;
	char	c;

	count = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		count += ft_print_c('-');
		n = -n;
	}
	if (n >= 10)
		count += ft_print_nbr(n / 10);
	c = (n % 10) + '0';
	count += ft_print_c(c);
	return (count);
}

int	ft_print_u(unsigned int n)
{
	int		count;
	char	c;

	count = 0;
	if (n >= 10)
		count += ft_print_u(n / 10);
	c = (n % 10) + '0';
	count += ft_print_c(c);
	return (count);
}

int	ft_print_x(unsigned int n)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		count += ft_print_x(n / 16);
	count += ft_print_c(base[n % 16]);
	return (count);
}

int	ft_print_mx(unsigned int n)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789ABCDEF";
	if (n >= 16)
		count += ft_print_mx(n / 16);
	count += ft_print_c(base[n % 16]);
	return (count);
}

int	ft_print_p(void *p)
{
	int			count;
	uintptr_t	address;

	count = 0;
	if (!p)
		return (ft_print_s("(nil)"));
	address = (uintptr_t)p;
	count += ft_print_s("0x");
	count += ft_pour_p(address);
	return (count);
}
