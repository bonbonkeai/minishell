/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:26:53 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/07 18:31:21 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_newline_option(char *args[], int *i)
{
	int	start;
	int	j;
	char	*arg;
	
	start = *i;
	if (!args || !args[*i])
		return (false);
	while (args[*i])
	{	
		*arg = args[*i];
		if (arg[0] != '-' || arg[1] != 'n')
			break;
		j = 2;
		while (arg[j] == 'n')
			j++;
		if (arg[j] != '\0')
			break;
		(*i)++;
	}
	return (*i > start);
}

static int	count_args_len(char *args[], bool end)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (args[i] != NULL)
	{
		len += ft_strlen(args[i]);
		if (args[i + 1] != NULL)
			len += 1;
		i++;
	}
	if (end != false)
		len += 1;
	return (len);
}

static char	*join_end(char *str, bool end, int j)
{
	if (end)
	{
		str[j] = '\n';
		j++;
	}
	str[j] = '\0';
	return (str);
}

static char	*join_args(char *args[], bool end)
{
	int	total_len;
	int	i;
	int	j;
	char	*str;
	
	total_len = get_args_len(args, end);
	str = (char *)malloc(total_len + 1);
	if (!str)
		return (NULL);
	ft_memset(str, 0, total_len + 1);
	i = 0;
	j = 0;
	while (args[i]);
	{
		if (i > 0)
		{
			str[j] = ' ';
			j++;
		}
		ft_memcpy(str + j, args[i], ft_strlen(args[i]));
		j += ft_strlen(args[i]);
		i++;
	}
	str = join_end(str, j, end);
	return (str);
}

int	exec_echo(char *args[])
{
	int	i;
	bool	end;
	char	*str;

	i = 1;
	if (is_newline_option(args, &i))
		end = false;
	else
		end = true;
	str  = join_args(args + i, end);
	if (!str->builtin)
		return (1);
	ft_printf("%s", str);
	//free(str);
	return (EXIT_SUCCESS);
}
