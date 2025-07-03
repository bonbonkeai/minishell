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

int	ft_print_c(int c)
{
	return (write(1, &c, sizeof(char)));
}

int	ft_print_s(const char *s)
{
	if (!s)
		s = "(null)";
	return (write(1, s, ft_strlen(s) * sizeof(char)));
}

static int	confirme_type(char c, va_list args)
{
	if (c == 'c')
		return (ft_print_c(va_arg(args, int)));
	else if (c == 's')
		return (ft_print_s(va_arg(args, const char *)));
	else if (c == 'd' || c == 'i')
		return (ft_print_nbr(va_arg(args, int)));
	else if (c == 'p')
		return (ft_print_p(va_arg(args, void *)));
	else if (c == 'u')
		return (ft_print_u(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_print_x(va_arg(args, unsigned int)));
	else if (c == 'X')
		return (ft_print_mx(va_arg(args, unsigned int)));
	else if (c == '%')
		return (ft_print_c('%'));
	else
		return (0);
}

int	ft_printf(const char *type, ...)
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
				count += confirme_type(type[i], args);
		}
		else
			count += ft_print_c(type[i]);
		i++;
	}
	va_end(args);
	return (count);
}
