/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:21:45 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/12 21:34:56 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_var_asin(char *arg, char **key, char **value)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		*key = ft_strndup(arg, eq - arg);
		*value = ft_strdup(eq + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = ft_strdup("");
	}
}

void	env_set_var(char *key, char *value, t_env **env)
{
	t_env	*cur;
	t_env	*new;

	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			free(cur->value);
			cur->value = ft_strdup(value);
			return ;
		}
		cur = cur->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = *env;
	*env = new;
}
	
int	builtin_export(char **argv, t_env **env)
{
	int	i;
	int	status;
	char	*key;
	char	*value;

	i = 0;
	status = EXIT_SUCCESS;
	while (argv[i])
	{
		split_var_asin(argv[i], &key, &value);
		if (!is_valid_var_name(key))
		{
			perror("export:");
			status = EXIT_FAILURE;
		}
		else
			env_set_var(key, value, env);
		free(key);
		free(value);
		i++;
	}
	return (status);
}
