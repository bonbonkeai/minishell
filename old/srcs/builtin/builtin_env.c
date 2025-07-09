/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:44:52 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/02 20:52:31 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	builtin_env(t_shell *sh)
// {
// 	t_env	*cur;

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

int	builtin_env(t_shell *sh)
{
	t_env	*cur;
	
	if (sh->cmd->args[1])
		return (ft_putstr_fd("This input is not accecpted\n", 2), 0);
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
