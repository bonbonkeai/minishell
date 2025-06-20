/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:28:32 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/05 19:58:27 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_pipes(t_cmd *cmd, t_shell *shell)
{
	if (cmd->next)
	{
		if (pipe(shell->new_pipe.fd) == -1)
		{
			perror("pipe failed");
			return (-1);
		}
	}
	return (0);
}
	
static int	wait_for_allpid(pid_t last_pid)
{
	int	status;
	pid_t	pid;

	status = exec_wait_pid(last_pid);
	if (status == -1)
		return (-1);
	while ((pid = wait(NULL)) != -1 || errno != ECHILD)
	{
		if (pid == -1)
		{
			if (errno != ECHILD)
			{
				perror("wait failed");
				return (-1);
			}
			break;
		}
	}
	errno = 0;
	return (status);
}

static void	iteration_pipe(t_cmd *cmd, t_shell *shell)
{
	if ((if_cmd_start(cmd)) == 1 || (if_cmd_simple(cmd)) != 2)
	{
		if (if_cmd_start(cmd) == 1)
		{
			printf("here i am WRONG!\n");
			return ;
		}
		else
			exec_simple(cmd, shell);
	}
	else
		return ;
	safe_close_all_pipes(shell);
}

int	exec_pipe(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;

	if (expand_heredoc_in_cmd_list(cmd, shell->env, shell->status) != 0)
		return (-1);
	while (cmd)
	{
		if (create_pipes(cmd, shell) == -1)
			return (-1);
		pid = fork();
		if (pid == -1)
		{
			safe_close_all_pipes(shell);
			break ;
		}
		if (pid == 0)
		{
			pipe_fork_child(&shell->new_pipe, &shell->old_pipe);
			iteration_pipe(cmd, shell);
			exit(EXIT_SUCCESS);
		}
		else
		{
			pipe_for_parent(&shell->new_pipe, &shell->old_pipe);
		}
		cmd = cmd->next;
	}
	return (wait_for_allpid(pid));
}
