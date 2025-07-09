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

int	ft_printnbr(int n, int fd)
{
	int		count;
	char	c;

	count = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		count += ft_printc(('-'), fd);
		n = -n;
	}
	if (n >= 10)
		count += ft_printnbr(n / 10, fd);
	c = (n % 10) + '0';
	count += ft_printc(c, fd);
	return (count);
}

int	ft_printu(unsigned int n, int fd)
{
	int		count;
	char	c;

	count = 0;
	if (n >= 10)
		count += ft_printu(n / 10, fd);
	c = (n % 10) + '0';
	count += ft_printc(c, fd);
	return (count);
}

int	ft_printx(unsigned int n, int fd)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		count += ft_printx((n / 16), fd);
	count += ft_printc((base[n % 16]), fd);
	return (count);
}

int	ft_printmx(unsigned int n, int fd)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789ABCDEF";
	if (n >= 16)
		count += ft_printmx((n / 16), fd);
	count += ft_printc((base[n % 16]), fd);
	return (count);
}

int	ft_printp(void *p, int fd)
{
	int			count;
	uintptr_t	address;

	count = 0;
	if (!p)
		return (ft_prints(("(nil)"), fd));
	address = (uintptr_t)p;
	count += ft_prints("0x", fd);
	count += ft_pourp(address, fd);
	return (count);
}
