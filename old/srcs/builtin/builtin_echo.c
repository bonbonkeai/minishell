/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:26:53 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/02 20:51:16 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_newline_option(char *args[], int *i)
{
	int		start;
	int		j;
	char	*arg;

	start = *i;
	if (!args || !args[*i])
		return (false);
	while (args[*i])
	{
		arg = args[*i];
		if (arg[0] != '-' || arg[1] != 'n')
			break ;
		j = 2;
		while (arg[j] == 'n')
			j++;
		if (arg[j] != '\0')
			break ;
		(*i)++;
	}
	return (*i > start);
}

int	builtin_echo(char *args[])
{
	int		i;
	bool	end;

	i = 1;
	end = true;
	if (is_newline_option(args, &i))
		end = false;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (end)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
