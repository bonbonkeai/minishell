/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:52:08 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/02 17:12:07 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_check_prexec(t_shell *sh, t_cmd *curr)
{
	if (!curr || !curr->cmd || curr->cmd[0] == '\0')
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
	if (if_cmd_builtin(sh) == 1)
	{
		touch_all_output_files(curr);
		resolve_redir(curr);
		return (exec_builtin_main(sh));
	}
	return (-2);
}

void	exec_child(t_shell *sh, t_cmd *curr, int status)
{
	touch_all_output_files(curr);
	resolve_redir(curr);
	if (curr->heredoc_fd != -1)
	{
		if (dup2(curr->heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc_fd");
			exit(EXIT_FAILURE);
		}
		close(curr->heredoc_fd);
	}
	else
		apply_input_red(sh);
	apply_output_red(sh);
	status = execve_bin(sh);
	exit(status);
}

int	exec_simple(t_shell *sh)
{
	t_cmd	*curr;
	int		precheck;
	int		status;
	int		pid;

	curr = sh->curr_cmd;
	status = 0;
	precheck = handle_check_prexec(sh, curr);
	if (precheck != -2)
		return (precheck);
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
	return (status);
}
