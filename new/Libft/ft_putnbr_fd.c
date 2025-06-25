/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:24:52 by jdu               #+#    #+#             */
/*   Updated: 2024/11/20 16:31:26 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
		return (write(fd, "-2147483648", 11), (void)0);
	if (n < 0)
	{
		c = '-';
		write(fd, &c, 1);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		c = (n % 10) + '0';
		write(fd, &c, 1);
	}
	if (n >= 0 && n < 10)
	{
		c = (n % 10) + '0';
		write(fd, &c, 1);
	}
}
/*
void ft_putnbr_fd(int n, int fd) 
{
    char c;

    if (n == -2147483648) 
    {
        write(fd, "-2147483648", 11);
        return ;
    }
    if (n < 0) 
    {
        write(fd, "-", 1);
        n = -n;
    }
    if (n >= 10)
        ft_putnbr_fd(n / 10, fd);
    c = (n % 10) + '0';
    write(fd, &c, 1);
}*/
