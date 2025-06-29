/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_setpath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:54:28 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/02 19:46:46 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_fullpath_cmd(const char *path, const char *cmd)
{
	int	len;
	char	*full_path;

	len = ft_strlen(path) + 1 + ft_strlen(cmd) + 1;
	full_path = (char *)malloc(sizeof(char) * (len));
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, path);
	ft_strcpy(full_path + ft_strlen(path), "/");
	ft_strcpy(full_path + ft_strlen(path) + 1, cmd);
	return (full_path);
}

// int	if_bin_access(char **bins, t_cmd *cmd)
// {
// 	int	i;
// 	char	*full_path;
// 	char	*command;

// 	command = cmd->cmd;
// 	if (!bins || !command)
// 		return (0);
	
// 	i = 0;
// 	while (bins[i])
// 	{
// 		full_path = join_fullpath_cmd(bins[i], command);
// 		if (!full_path)
// 			return (0);
// 		if (access(full_path, X_OK & F_OK) == 0)
// 		{           
// 			cmd->pth = full_path;
// 			return (1);
// 		}
// 		free(full_path);
// 		i++;
// 	}
// 	return (0);
// }

// int	if_bin_access(char **bins, t_shell *sh)
// {
// 	int	i;
// 	char	*full_path;
// 	char	*command;

// 	command = sh->cmd->cmd;
// 	if (!bins || !command)
// 		return (0);
	
// 	i = 0;
// 	while (bins[i])
// 	{
// 		full_path = join_fullpath_cmd(bins[i], command);
// 		if (!full_path)
// 			return (0);
// 		if (access(full_path, X_OK & F_OK) == 0)
// 		{           
// 			sh->cmd->pth = full_path;
// 			return (1);
// 		}
// 		free(full_path);
// 		i++;
// 	}
// 	return (0);
// }

int	if_bin_access(char **bins, t_shell *sh)
{
	int	i;
	char	*full_path;
	char	*command;

	command = sh->curr_cmd->cmd;
	if (!bins || !command)
		return (0);
	i = 0;
	while (bins[i])
	{
		full_path = join_fullpath_cmd(bins[i], command);
		if (!full_path)
			return (0);
		if (access(full_path, X_OK & F_OK) == 0)
		{           
			sh->curr_cmd->pth = full_path;
			return (1);
		}
		free(full_path);
		i++;
	}
	return (0);
}

int	if_abs_bin_access(char *command)
{
	if (!command)
		return (0);
	if (command[0] == '/' && access(command, X_OK) == 0)
		return (1);
	return (0);
}

// char	*get_env_var_value(t_env *env, char *name)
// {
// 	t_env	*cur;

// 	cur = env;
// 	if (!name)
// 		return NULL;
// 	while (cur)
// 	{
// 		if (ft_strcmp(cur->key, name) == 0)
// 			return (cur->value);
// 		cur = cur->next;
// 	}
// 	return (NULL);
// }

char	*get_env_var_value(t_shell *sh, char *name)
{
	t_env	*cur;

	if (!sh || !sh->env)
		return (NULL);
	cur = sh->env;
	if (!name)
		return (NULL);
	while (cur)
	{
		// ft_printf("currkey %s\n", cur->key);
		if (cur->key)
		{
			if (ft_strcmp(cur->key, name) == 0)
				return (cur->value);
		}
		cur = cur->next;
	}
	return (NULL);
}