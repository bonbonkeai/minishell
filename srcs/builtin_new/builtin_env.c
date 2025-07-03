/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:44:52 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/12 18:47:11 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_env *env)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (cur->value)
			ft_printf("%s=%s\n", cur->key, cur->value);
		else
			ft_printf("%s=\n", cur->key);
		cur = cur->next;
	}
	return (0);
}
