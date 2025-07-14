/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:46:41 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/09 14:27:49 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_error(const char *msg, const char *arg)
{
	if (!msg)
		msg = "";
	if (!arg)
		arg = "";
	write(2, "minishell: exit: ", 17);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

static int	parse_number(const char *str, long *result, int sign)
{
	int	digit;

	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		digit = *str - '0';
		if (sign == 1 && *result > (LONG_MAX - digit) / 10)
			return (0);
		if (sign == -1 && - *result < (LONG_MIN + digit) / 10)
			return (0);
		*result = *result * 10 + digit;
		str++;
	}
	return (1);
}

static long	str_to_int(const char *str, long *out)
{
	long	result;
	int		sign;

	if (!str)
		return (0);
	result = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!*str)
		return (0);
	if (!parse_number(str, &result, sign))
		return (0);
	*out = result * sign;
	return (1);
}

static void	exit_free(t_shell *sh)
{
	free_shell(sh);
	rl_clear_history();
}

// int	builtin_exit(t_shell *sh, char **argv)
// {
// 	long	code;
// 	int		len;

// 	code = 0;
// 	len = 0;
// 	while (argv[len])
// 		len++;
// 	write(STDOUT_FILENO, "exit\n", 5);
// 	if (!str_to_int(argv[1], &code))
// 	{
// 		put_error("numeric argument required", argv[1]);
// 		exit_free(sh);
// 		exit(2);
// 	}
// 	if (len > 2)
// 	{
// 		write(2, "minishell: exit: too many arguments\n", 37);
// 		return (1);
// 	}
// 	// exit_free(sh);
// 	rl_clear_history();
// 	exit((unsigned char)code);
// }

int	builtin_exit(t_shell *sh, char **argv)
{
	long	code;
	int		len;

	code = 0;
	len = 0;
	while (argv[len])
		len++;
	write(STDOUT_FILENO, "exit\n", 5);
	if (len == 1)
		code = exec_exit_status(0, 0);
	else if (len > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		sh->status = 1;
		return (1);
	}
	else if (!str_to_int(argv[1], &code))
	{
		put_error("numeric argument required", argv[1]);
		exit_free(sh);
		exit(2);
	}
	exit_free(sh);
	exit((unsigned char)code);
}
