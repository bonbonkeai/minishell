/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:40:23 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/01 20:50:24 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_args(t_cmd *cmd)
{
	if (cmd->args)
		return (cmd->args);
	return (NULL);
}

char	*get_path(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**bins;
	char	*pathlist;

	path = NULL;
	if (!if_cmd_builtin(cmd))
	{
		if (if_abs_bin_access(cmd->cmd) == 1)
			path = cmd->cmd;
		else
		{
			pathlist = get_env_var_value(env, "PATH");
			bins = ft_split(pathlist, ':');
			if (if_bin_access(bins, cmd) == 1)
				path = cmd->pth;
		}
	}
	return (path);
}

static int	count_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}
static char	*join_key_value(const char *key, const char *value)
{
	int	i;
	int	j;
	int	total;
	char	*res;

	total = ft_strlen(key) + 1 + ft_strlen(value) + 1;
	res = malloc(total);
	if (!res)
		return (NULL);
	i = 0;
	while (key[i])
	{
		res[i] = key[i];
		i++;
	}
	res[i] = '=';
	i++;
	j = 0;
	while (value[j])
	{
		res[i] = value[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	**get_env_variables(t_env *env)
{
	char	**envp;
	int	count;
	int	i;
	int	k;

	count = count_env(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i] = join_key_value(env->key, env->value);
		if (!envp[i])
		{
			k = 0;
			while (k < i)
			{
				free(envp[k]);
				k++;
			}
			free(envp);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
