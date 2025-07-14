/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:52:08 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/11 20:25:17 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exec_if_builtin(t_shell *sh, t_cmd *curr)
{
	int	status;

	status = -1;
	if (if_cmd_builtin(sh) == 1)
	{
		status = exec_builtin_main(sh, curr);
		return (status);
	}
	return (status);
}

void	exec_child(t_shell *sh, t_cmd *curr, int status)
{
	if (resolve_redir(sh, curr, NULL) < 0)
	{
		free_shell(sh);
		exit(1);
	}
	if (sh->cmd && sh->cmd->is_dummy_cmd)
	{
		status = handle_dummy_cmd(sh, sh->cmd);
		free_shell(sh);
		exit(status);
	}
	close_all_heredoc_fd(sh->cmd);
	signal_default();
	status = execve_bin(sh);
	free_shell(sh);
	exit(status);
}

static int	pre_exec_and_check_builtin(t_shell *sh, t_cmd *cmd, int *status)
{
	int	res_parent;

	res_parent = handle_check_prexec(sh, cmd);
	if (res_parent != -1)
		return (res_parent);
	*status = check_exec_if_builtin(sh, cmd);
	return (-1);
}

int	exec_simple(t_shell *sh)
{
	t_cmd	*curr;
	int		status;
	int		pid;
	int		res_parent;

	curr = sh->curr_cmd;
	res_parent = pre_exec_and_check_builtin(sh, curr, &status);
	if (res_parent != -1)
		return (res_parent);
	if (status == -1)
	{
		pid = fork();
		if (pid == 0)
			exec_child(sh, curr, status);
		else if (pid > 0)
		{
			curr->pid = pid;
			return (exec_wait_pid(pid));
		}
		else
			return (perror("fork failed"), 1);
	}
	return (status);
}

// int	exec_simple(t_shell *sh)
// {
// 	t_cmd	*curr;
// 	int		status;
// 	int		pid;
// 	int		res_parent;

// 	curr = sh->curr_cmd;
// 	res_parent = handle_check_prexec(sh, curr);
// 	if (res_parent != -1)
// 		return (res_parent);
// 	status = check_exec_if_builtin(sh, curr);
// 	if (status == -1)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 			exec_child(sh, curr, status);
// 		else if (pid > 0)
// 		{
// 			curr->pid = pid;
// 			return (exec_wait_pid(pid));
// 		}
// 		else
// 		{
// 			perror("fork failed");
// 			return (1);
// 		}
// 	}
// 	return (status);
// }
