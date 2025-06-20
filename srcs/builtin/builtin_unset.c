/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:51:09 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/12 21:06:17 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_var_char(char c)
{
	if (( c >= 'A' && c <= 'Z') || \
			(c >= 'a' && c <= 'z') || \
			(c >= '0' && c <= '9') || \
			c == '_')
		return (1);
	return (0);
}

int	is_valid_var_name(char *var)
{
	int	i;

	if (!var || var[0] == '\0')
		return (0);
	if (!((var[0] >= 'A' && var[0] <= 'Z') || \
		(var[0] >= 'a' && var[0] <= 'z') || \
			var[0] == '_'))
		return (0);
	if (!var || var[0] == '\0')
		return (0);
	i = 1;
	while (var[i])
	{
		if (!is_var_char(var[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	env_unset_var(char *var, t_env **env)
{
	t_env	*prev;
	t_env	*curr;
	t_env	*temp;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, var) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			temp = curr;
			free(temp);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	builtin_unset(t_env **env, char **argv)
{
	int	i;
	int	status;
	char	*var;

	i = 1;
	status = EXIT_SUCCESS;
	while (argv[i])
	{
		var = argv[i];
		if (!is_valid_var_name(var))
		{
			perror("unset: ");
			status = EXIT_FAILURE;
		}
		else
			env_unset_var(var, env);
		i++;
	}
	return (status);
}
