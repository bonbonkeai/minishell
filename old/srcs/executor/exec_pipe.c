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

static int	create_pipes(t_shell *sh, t_cmd *curr)
{
	// sh->new_pipe.fd[0] = -1;
	// sh->new_pipe.fd[1] = -1;
	if (curr->next)
	{
		// ft_fprintf(2, "Creating pipe for cmd: %s\n", curr->cmd);
		if (pipe(sh->new_pipe.fd) == -1)
		{
			perror("pipe failed");
			return (-1);
		}
	}
	// else
	// 	ft_fprintf(2, "Not creating pipe for last command: %s\n", curr->cmd);
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


static void	iteration_pipe(t_shell *sh)
{
	if (!sh->current_cmd)
		return;
	if ((if_cmd_start(sh->current_cmd)) == 1 || (if_cmd_simple(sh->current_cmd)) != 2)
	{
		if (if_cmd_start(sh->current_cmd) == 1)
		{
			printf("here i am WRONG!\n");
			return ;
		}
		else
			exec_simple(sh);
	}
	else
		return ;
	safe_close_all_pipes(sh);
}

int	exec_pipe(t_shell *sh)
{
	pid_t	pid;
	t_cmd *curr;

	if (expand_heredoc_in_cmd_list(sh) != 0)
		return (-1);
	curr = sh->cmd;
	while (curr)
	{
		int is_last = (curr->next == NULL);
		sh->current_cmd = curr;
		sh->new_pipe.fd[0] = -1;
		sh->new_pipe.fd[1] = -1;
		if (create_pipes(sh, curr) == -1)
			return (-1);
		pid = fork();
		if (pid == -1)
		{
			safe_close_all_pipes(sh);
			break ;
		}
		if (pid == 0)
		{
			pipe_fork_child(&sh->new_pipe, &sh->old_pipe, is_last);
			iteration_pipe(sh);
			exit(EXIT_SUCCESS);
		}
		else
		{
			pipe_for_parent(&sh->new_pipe, &sh->old_pipe);
		}
		curr = curr->next;
	}
	return (wait_for_allpid(pid));
}