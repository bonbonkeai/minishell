/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:58:08 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/09 14:42:54 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_wait_pid(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		status = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

static void	waitchild_status(pid_t pid, int status, t_pipe_data *data, int *fs)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT && pid == data->pid)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		else if (sig == SIGINT && data->newline == 0)
		{
			ft_putstr_fd("\n", STDERR_FILENO);
			data->newline = 1;
		}
		if (pid == data->pid)
			*fs = 128 + sig;
	}
	else if (WIFEXITED(status))
	{
		if (pid == data->pid)
			*fs = WEXITSTATUS(status);
	}
}

int	wait_for_allpid( t_pipe_data *data)
{
	int		status;
	pid_t	pid;
	int		final_status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		waitchild_status(pid, status, data, &final_status);
	}
	if (errno != ECHILD)
	{
		perror("wait failed");
		return (-1);
	}
	return (final_status);
}
