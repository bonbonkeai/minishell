/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:44:52 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/09 14:27:07 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// int	builtin_env(t_shell *sh)
// {
// 	t_env	*cur;	
// 	if (sh->cmd->args[1])
// 		return (ft_putstr_fd("This input is not accecpted\n", 2), 127);
// 	cur = sh->env;
// 	while (cur)
// 	{
// 		if (cur->exported)
// 		{
// 			if (cur->value && cur->value[0] != '\0')
// 				ft_printf("%s=%s\n", cur->key, cur->value);
// 			else if (cur->value && cur->value[0] == '\0')
// 				ft_printf("%s=\n", cur->key);
// 		}
// 		cur = cur->next;
// 	}
// 	return (0);
// }
static void	print_env_null_terminated(t_shell *sh)
{
	t_env	*cur;

	cur = sh->env;
	while (cur)
	{
		if (cur->exported)
		{
			if (cur->value)
			{
				ft_printf("%s=%s", cur->key, cur->value);
				write(1, "\0", 1);
			}
		}
		cur = cur->next;
	}
}

int	builtin_env(t_shell *sh)
{
	t_env	*cur;
	char	*arg;

	arg = sh->cmd->args[1];
	if (arg)
	{
		if (ft_strncmp(arg, "--null", 6) == 0)
			return (print_env_null_terminated(sh), 0);
		else if (arg[0] == '-' && arg[1] != '\0')
			return (ft_putstr_fd(ERR_ENV_I, STDERR_FILENO), 125);
		return (ft_putstr_fd(ERR_ENV_I, STDERR_FILENO), 127);
	}
	cur = sh->env;
	while (cur)
	{
		if (cur->exported)
		{
			if (cur->value && cur->value[0] != '\0')
				ft_printf("%s=%s\n", cur->key, cur->value);
			else if (cur->value && cur->value[0] == '\0')
				ft_printf("%s=\n", cur->key);
		}
		cur = cur->next;
	}
	return (0);
}
