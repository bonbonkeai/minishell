/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:14:17 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/14 14:47:15 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_abs_or_rel_path(t_cmd *curr, char **path)
{
	if (access(curr->cmd, F_OK) != 0)
	{
		print_cmd_error(curr->cmd, "No such file or directory");
		return (127);
	}
	if (access(curr->cmd, X_OK) != 0)
	{
		print_cmd_error(curr->cmd, "Permission denied");
		return (126);
	}
	*path = ft_strdup(curr->cmd);
	if (!*path)
		return (127);
	return (0);
}

static int	get_cmd_path(t_shell *sh, char **path)
{
	t_cmd	*curr;

	curr = sh->curr_cmd;
	if (curr->cmd[0] == '/' || (curr->cmd[0] == '.' && curr->cmd[1] == '/'))
		return (check_abs_or_rel_path(curr, path));
	*path = get_path(sh);
	if (!*path)
	{
		print_cmd_error(curr->cmd, "command not found");
		return (127);
	}
	return (0);
}

static int	prepare_args(t_shell *sh, char **path, char ***arg, char ***vars)
{
	int	ret;

	ret = get_cmd_path(sh, path);
	if (ret != 0)
		return (ret);
	*arg = get_args(sh);
	if (!*arg)
	{
		free(*path);
		return (127);
	}
	*vars = get_env_variables(sh);
	if (!*vars)
	{
		free(*path);
		free_paths(*arg);
		return (127);
	}
	return (0);
}

static int	check_exec(char *path, char **arg, char **vars, t_shell *sh)
{
	if (check_cmd_standard(sh))
	{
		if (access(path, X_OK) == -1)
		{
			ft_fprintf(2, "Permission denied or command not executable");
			return (2);
		}
		if (execve(path, arg, vars) == -1)
		{
			perror("execve");
			free(path);
			free_paths(arg);
			free_paths(vars);
			return (EXIT_FAILURE);
		}
		ft_fprintf(2, "Command execution failed");
		return (1);
	}
	else
	{
		execve(path, arg, vars);
		ft_fprintf(2, "Command execution failed");
		return (1);
	}
}

int	execve_bin(t_shell *sh)
{
	char	*path;
	char	**arg;
	char	**vars;
	int		ret;

	signal_default();
	ret = prepare_args(sh, &path, &arg, &vars);
	if (ret != 0)
		return (ret);
	ret = check_exec(path, arg, vars, sh);
	return (ret);
}
