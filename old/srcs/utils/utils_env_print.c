/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:26:51 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/02 19:38:17 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*cur;

	count = 0;
	cur = env;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

static t_env	**env_list_to_array(t_env *env, int count)
{
	t_env	**env_array;
	t_env	*cur;
	int		i;

	i = 0;
	cur = env;
	env_array = malloc(sizeof(t_env *) * count);
	if (!env_array)
		return (NULL);
	while (cur)
	{
		env_array[i++] = cur;
		cur = cur->next;
	}
	return (env_array);
}

static void	print_exported_env(t_env **ea, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (ea[i]->exported)
			ft_printf("export %s=\"%s\"\n", ea[i]->key, ea[i]->value);
		else
			ft_printf("export %s\n", ea[i]->key);
		i++;
	}
}

void	export_print_env(t_shell *sh)
{
	int		count;
	t_env	**env_array;

	count = count_env_vars(sh->env);
	if (count == 0)
		return ;
	env_array = env_list_to_array(sh->env, count);
	if (!env_array)
		return ;
	print_exported_env(env_array, count);
	free(env_array);
}
