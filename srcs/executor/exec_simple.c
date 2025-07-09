/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:52:08 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/09 14:42:01 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_check_prexec(t_shell *sh, t_cmd *curr)
{
	if (!curr || (!curr->cmd && !curr->args && curr->heredoc))
		return (0);
	if (!curr->cmd || curr->cmd[0] == '\0')
	{
		print_cmd_error(curr->cmd, "command not found");
		return (127);
	}
	if (is_empty_command(sh->trimmed_prompt))
	{
		print_cmd_error(sh->trimmed_prompt, "command not found");
		return (127);
	}
	if (is_directory(curr->cmd))
	{
		print_cmd_error(curr->cmd, "Is a directory");
		return (126);
	}
	return (-1);
}

// int	check_exec_if_builtin(t_shell *sh, t_cmd *curr)
// {
// 	int	status;

// 	status = -1;
// 	(void)curr;
// 	if (if_cmd_builtin(sh) == 1)
// 	{
// 		// if (!touch_all_output_files(curr)) ATTENTION!!
// 		// {
// 		// 	free_shell(sh);
// 		// 	exit(1);
// 		// }
// 		//resolve_redir(sh, curr);
// 		return (exec_builtin_main(sh));
// 		// return (status);
// 	}
// 	return (status);
// }

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
	resolve_redir(sh, curr, NULL);
	close_all_heredoc_fd(sh->cmd);
	signal_default();
	status = execve_bin(sh);
	exit(status);
}

int	exec_simple(t_shell *sh)
{
	t_cmd	*curr;
	int		status;
	int		pid;
	int		res_parent;

	curr = sh->curr_cmd;
	res_parent = handle_check_prexec(sh, curr);
	if (res_parent != -1)
		return (res_parent);
	status = check_exec_if_builtin(sh, curr);
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
		{
			perror("fork failed");
			return (1);
		}
	}
	return (status);
}
