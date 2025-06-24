/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:46:41 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/12 19:56:24 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static void	put_error(const char *msg, const char *arg)
{
	write(2, "exit: ", 6);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}
static long	str_to_int(const char *str)
{
	long	result;
	int	sign;

	result = 0;
	sign = 1;

	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	builtin_exit(char **argv)
{
	long	code;
	int	len;

	code = 0;
	len = 0;
	while (argv[len])
		len++;
	//printf("Ieh3uehu32");
	//write(STDOUT_FILENO, "exit\n", 5);
	if (argv[1] && !is_numeric(argv[1]))
	{
		//printf("IDEOHWDEI");
		put_error("numeric argument required", argv[1]);
		exit(255);
	}
	if (len > 2)
	{
		//printf("eouhweudh");
		write(2, "exit: too many arguments\n", 26);
		return (1);
	}
	if (argv[1])
		code = str_to_int(argv[1]);
    exit((unsigned char)code);
}       
