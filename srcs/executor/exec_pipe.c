/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:46:13 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/13 19:38:00 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	iteration_pipe(t_shell *sh)
{
	int	status;

	if (!sh || !sh->curr_cmd)
		return (0);
	if (if_cmd_start(sh->curr_cmd) == 1)
		return (0);
	if (if_cmd_simple(sh->curr_cmd) != 2)
	{
		status = exec_simple_pipe(sh);
		safe_close_all_pipes(sh);
		free_shell(sh);
		exit(status);
	}
	safe_close_all_pipes(sh);
	return (0);
}

static int	handle_pipe(t_shell *sh, t_cmd *curr, int last_cmd, pid_t *pid)
{
	if (prepare_pipe_command(sh, curr) == -1)
		return (-1);
	if (if_cmd_builtin(sh) && command_num(sh->cmd) == 1)
	{
		sh->status = exec_builtin_main(sh, curr);
		return (1);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork failed");
		return (2);
	}
	else if (*pid == 0)
	{
		pipe_fork_child(sh, &sh->new_pipe, &sh->old_pipe, last_cmd);
		iteration_pipe(sh);
		exit(EXIT_FAILURE);
	}
	else
	{
		curr->pid = *pid;
		pipe_for_parent(&sh->new_pipe, &sh->old_pipe);
	}
	return (0);
}

static int	wait_for_child(pid_t last_pid)
{
	int	status;

	status = wait_for_allpid(last_pid);
	exec_exit_status(1, status);
	return (status);
}

static int	process_pipe_command(t_shell *sh, t_cmd *curr, \
		int last_cmd, t_pipe_data *data)
{
	int	ret;

	ret = handle_pipe(sh, curr, last_cmd, &data->pid);
	if (ret == -1)
		return (-1);
	if (ret == 1)
	{
		data->status = sh->status;
		return (1);
	}
	if (ret == 2)
		return (2);
	return (0);
}

int	exec_pipe(t_shell *sh)
{
	t_cmd		*curr;
	t_pipe_data	data;
	int			ret;
	int			last_cmd;

	curr = sh->cmd;
	data.status = 0;
	while (curr)
	{
		last_cmd = is_last_cmd(curr);
		ret = process_pipe_command(sh, curr, last_cmd, &data);
		if (ret == -1)
			return (-1);
		if (ret == 1)
		{
			break ;
		}
		if (ret == 2)
			return (1);
		curr = curr->next;
	}
	if (ret == 1)
		return (data.status);
	return (wait_for_child(data.pid));
}
