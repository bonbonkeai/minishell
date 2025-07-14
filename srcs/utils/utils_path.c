/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:33:59 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/11 20:32:19 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_cmd_path_from_env(t_shell *sh)
{
	char	*pathlist;
	char	**bins;
	char	*cmd;
	char	*resolved;

	cmd = sh->curr_cmd->cmd;
	pathlist = get_env_var_value(sh, "PATH");
	if (!pathlist || *pathlist == '\0')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	bins = ft_split(pathlist, ':');
	if (!bins)
		return (NULL);
	if (if_bin_access(bins, sh) == 1)
		resolved = sh->curr_cmd->pth;
	else
		resolved = NULL;
	free_paths(bins);
	return (resolved);
}

char	*get_path(t_shell *sh)
{
	char	*path;

	path = NULL;
	if (!sh->curr_cmd || !sh->curr_cmd->cmd)
		return (NULL);
	if (!if_cmd_builtin(sh))
	{
		if (if_abs_bin_access(sh->curr_cmd->cmd) == 1)
			path = sh->curr_cmd->cmd;
		else
			path = find_cmd_path_from_env(sh);
	}
	return (path);
}
