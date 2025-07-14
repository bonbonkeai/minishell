/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:39:29 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/11 20:26:30 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_stdin(t_cmd *cmd, t_pipe *old_pipe)
{
	if (cmd && cmd->heredoc_fd != -1)
	{
		if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc_fd");
			exit(EXIT_FAILURE);
		}
	}
	else if (old_pipe->fd[0] != -1)
	{
		if (dup2(old_pipe->fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 old_pipe->fd[0]");
			exit(EXIT_FAILURE);
		}
	}
}

static void	setup_stdout_and_close(t_cmd *cmd, t_pipe *old_pipe, \
	t_pipe *new_pipe, int last)
{
	if (!last && new_pipe->fd[1] != -1)
	{
		if (dup2(new_pipe->fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 new_pipe->fd[1]");
			exit(EXIT_FAILURE);
		}
	}
	if (cmd && cmd->heredoc_fd != -1)
	{
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
	if (old_pipe->fd[0] != -1)
		close(old_pipe->fd[0]);
	if (old_pipe->fd[1] != -1)
		close(old_pipe->fd[1]);
	if (new_pipe->fd[0] != -1)
		close(new_pipe->fd[0]);
	if (new_pipe->fd[1] != -1)
		close(new_pipe->fd[1]);
}

void	pipe_fork_child(t_shell *sh, t_pipe *new_pipe, \
		t_pipe *old_pipe, int last)
{
	t_cmd	*cmd;

	cmd = sh->curr_cmd;
	setup_stdin(cmd, old_pipe);
	setup_stdout_and_close(cmd, old_pipe, new_pipe, last);
	if (resolve_redir(sh, cmd, NULL) < 0)
	{
		free_shell(sh);
		exit(1);
	}
	iteration_pipe(sh);
	exit(EXIT_FAILURE);
}

void	pipe_for_parent(t_pipe *new_pipe, t_pipe *old_pipe)
{
	if (old_pipe->fd[0] != -1)
		close(old_pipe->fd[0]);
	if (old_pipe->fd[1] != -1)
		close(old_pipe->fd[1]);
	old_pipe->fd[0] = new_pipe->fd[0];
	old_pipe->fd[1] = new_pipe->fd[1];
	new_pipe->fd[0] = -1;
	new_pipe->fd[1] = -1;
}

void	safe_close_all_pipes(t_shell *shell)
{
	if (shell->new_pipe.fd[0] > STDERR_FILENO)
	{
		close(shell->new_pipe.fd[0]);
		shell->new_pipe.fd[0] = -1;
	}
	if (shell->new_pipe.fd[1] > STDERR_FILENO)
	{
		close(shell->new_pipe.fd[1]);
		shell->new_pipe.fd[1] = -1;
	}
	if (shell->old_pipe.fd[0] > STDERR_FILENO)
	{
		close(shell->old_pipe.fd[0]);
		shell->old_pipe.fd[0] = -1;
	}
	if (shell->old_pipe.fd[1] > STDERR_FILENO)
	{
		close(shell->old_pipe.fd[1]);
		shell->old_pipe.fd[1] = -1;
	}
}
