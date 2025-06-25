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

char	**get_args(t_shell *sh)
{
	if (sh->current_cmd->args)
		return (sh->current_cmd->args);
	return (NULL);
}

char	*get_path(t_shell *sh)
{
	char	*path;
	char	**bins;
	char	*pathlist;

	path = NULL;
	if (!if_cmd_builtin(sh))
	{
		if (if_abs_bin_access(sh->current_cmd->cmd) == 1)
			path = sh->current_cmd->cmd;
		else
		{
			pathlist = get_env_var_value(sh, "PATH");
			bins = ft_split(pathlist, ':');
			if (if_bin_access(bins, sh) == 1)
				path = sh->current_cmd->pth;
			int i = 0;
			if (bins)
            {
				while (bins[i])
				{
					free(bins[i]);
					i++;
				}
            	free(bins);
			}
		}
	}
	return (path);
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

static int	count_env(t_shell *sh)
{
	int	count = 0;
	t_env *tmp = sh->env;  // 假设 t_env 是环境变量节点类型

	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**get_env_variables(t_shell *sh)
{
	int		count = count_env(sh);
	char	**envp = malloc(sizeof(char *) * (count + 1));
	t_env	*tmp = sh->env;
	int		i = 0;

	if (!envp)
		return (NULL);
	while (tmp)
	{
		envp[i] = join_key_value(tmp->key, tmp->value);
		if (!envp[i])
		{
			while (--i >= 0)
				free(envp[i]);
			free(envp);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
