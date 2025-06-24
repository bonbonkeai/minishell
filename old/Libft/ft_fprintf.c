/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:32:45 by jdu               #+#    #+#             */
/*   Updated: 2024/11/20 19:18:59 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printc(int c, int fd)
{
	return (write(fd, &c, sizeof(char)));
}

int	ft_prints(const char *s, int fd)
{
	if (!s)
		s = "(null)";
	return (write(fd, s, ft_strlen(s) * sizeof(char)));
}

static int	confirme_type(int fd, char c, va_list args)
{
	if (c == 'c')
		return (ft_printc(va_arg(args, int), fd));
	else if (c == 's')
		return (ft_prints(va_arg(args, const char *), fd));
	else if (c == 'd' || c == 'i')
		return (ft_printnbr(va_arg(args, int), fd));
	else if (c == 'p')
		return (ft_printp(va_arg(args, void *), fd));
	else if (c == 'u')
		return (ft_printu(va_arg(args, unsigned int), fd));
	else if (c == 'x')
		return (ft_printx(va_arg(args, unsigned int), fd));
	else if (c == 'X')
		return (ft_printmx(va_arg(args, unsigned int), fd));
	else if (c == '%')
		return (ft_printc(('%'), fd));
	else
		return (0);
}

int	ft_fprintf(int fd, const char *type, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!type)
		return (-1);
	va_start(args, type);
	while (type[i])
	{
		if (type[i] == '%')
		{
			i++;
			if (ft_is_type(type[i]) == 1)
				count += confirme_type(fd, type[i], args);
		}
		else
			count += ft_printc(type[i], fd);
		i++;
	}
	va_end(args);
	return (count);
}
