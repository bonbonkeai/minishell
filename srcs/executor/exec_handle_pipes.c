/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:39:29 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/05 20:52:00 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	pipe_fork_child(t_pipe *new_pipe, t_pipe *old_pipe)
{
	if (old_pipe->fd[0] != -1)
		dup2(old_pipe->fd[0], STDIN_FILENO);
	if (new_pipe->fd[1] != -1)
		dup2(new_pipe->fd[1], STDOUT_FILENO);
	if (old_pipe->fd[0] != -1)
		close(old_pipe->fd[0]);
	if (old_pipe->fd[1] != -1)
		close(old_pipe->fd[1]);
	if (new_pipe->fd[0] != -1)
		close(new_pipe->fd[0]);
	if (new_pipe->fd[1] != -1)
		close(new_pipe->fd[1]);
} */

void	pipe_fork_child(t_pipe *new_pipe, t_pipe *old_pipe)
{
	if (old_pipe->fd[0] != -1)
	{
		if (dup2(old_pipe->fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 old_pipe->fd[0]");
			exit(EXIT_FAILURE);
		}
	}
	if (new_pipe->fd[1] != -1)
	{
		if (dup2(new_pipe->fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 new_pipe->fd[1]");
			exit(EXIT_FAILURE);
		}
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

// void	initialize_pipe(t_shell *shell)
// {
// 	shell->old_pipe.fd[0] = -1;
// 	shell->old_pipe.fd[1] = -1;
// 	shell->new_pipe.fd[0] = -1;
// 	shell->new_pipe.fd[1] = -1;
// }

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
