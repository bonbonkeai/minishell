/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:40:23 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/03 16:07:07 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_args(t_shell *sh)
{
	if (!sh->curr_cmd)
		return (NULL);
	if (sh->curr_cmd->args)
		return (sh->curr_cmd->args);
	return (NULL);
}

static int	count_env(t_shell *sh)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = sh->env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	*join_key_value(const char *key, const char *value)
{
	int		i;
	int		j;
	int		total;
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
		res[i++] = value[j++];
	}
	res[i] = '\0';
	return (res);
}

// char	*get_path(t_shell *sh)
// {
// 	char	*path;
// 	char	**bins;
// 	char	*pathlist;

// 	path = NULL;
// 	if (!sh->curr_cmd || !sh->curr_cmd->cmd)
// 		return (NULL);
// 	if (!if_cmd_builtin(sh))
// 	{
// 		if (if_abs_bin_access(sh->curr_cmd->cmd) == 1)
// 			path = sh->curr_cmd->cmd;
// 		else
// 		{
// 			pathlist = get_env_var_value(sh, "PATH");
// 			if (!pathlist)
// 				return (NULL);
// 			bins = ft_split(pathlist, ':');
// 			if (!bins)
// 				return (NULL);
// 			if (if_bin_access(bins, sh) == 1)
// 				path = sh->curr_cmd->pth;
// 			free_paths(bins);
// 		}
// 	}
// 	return (path);
// }

char	**get_env_variables(t_shell *sh)
{
	int		count;
	char	**envp;
	t_env	*tmp;
	int		i;

	i = 0;
	count = count_env(sh);
	envp = malloc(sizeof(char *) * (count + 1));
	tmp = sh->env;
	if (!envp)
		return (NULL);
	while (tmp)
	{
		envp[i] = join_key_value(tmp->key, tmp->value);
		if (!envp[i++])
		{
			while (--i >= 0)
				free(envp[i]);
			free(envp);
			return (NULL);
		}
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
