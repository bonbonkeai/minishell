/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:46:13 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/09 14:38:35 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prepare_pipe_command(t_shell *sh, t_cmd *curr)
{
	sh->curr_cmd = curr;
	sh->new_pipe.fd[0] = -1;
	sh->new_pipe.fd[1] = -1;
	if (curr->next)
	{
		if (pipe(sh->new_pipe.fd) == -1)
		{
			perror("pipe failed");
			return (-1);
		}
	}
	return (0);
}

// static int	is_last_cmd(t_cmd *cmd)
// {
// 	if (cmd->next == NULL)
// 		return (1);
// 	return (0);
// }

// static int	wait_for_allpid(pid_t last_pid)
// {
// 	int		status;
// 	pid_t	pid;

// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// 	status = exec_wait_pid(last_pid);
// 	if (status == -1)
// 		return (-1);
// 	errno = 0;
// 	while (1)
// 	{
// 		pid = wait(NULL);
// 		if (pid == -1)
// 		{
// 			if (errno == ECHILD)
// 				break ;
// 			else
// 			{
// 				perror("wait failed");
// 				return (-1);
// 			}
// 			break ;
// 		}
// 	}
// 	return (status);
// }

// static int	wait_for_allpid(pid_t last_pid)
// {
// 	int		status;
// 	pid_t	pid;
// 	int		final_status = 0;

// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// 	while ((pid = waitpid(-1, &status, 0)) != -1)
// 	{
// 		if (WIFSIGNALED(status))
// 		{
// 			int sig = WTERMSIG(status);
// 			if (sig == SIGQUIT && pid == last_pid)  
// 				ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
// 			else if (sig == SIGINT)
// 				ft_putstr_fd("\n", STDERR_FILENO);
// 			if (pid == last_pid)
// 				final_status = 128 + sig;
// 		}
// 		else if (WIFEXITED(status))
// 		{
// 			if (pid == last_pid)
// 				final_status = WEXITSTATUS(status);
// 		}
// 	}
// 	if (errno != ECHILD)
// 	{
// 		perror("wait failed");
// 		return (-1);
// 	}
// 	return final_status;
// }

void	close_all_heredoc_fd(t_cmd *cmd_list)
{
	t_cmd	*curr;

	curr = cmd_list;
	while (curr)
	{
		if (curr->heredoc_fd != -1)
		{
			close(curr->heredoc_fd);
			curr->heredoc_fd = -1;
		}
		curr = curr->next;
	}
}

static void	iteration_pipe(t_shell *sh)
{
	if (!sh->curr_cmd)
		return ;
	if ((if_cmd_start(sh->curr_cmd)) == 1 || (if_cmd_simple(sh->curr_cmd)) != 2)
	{
		if (if_cmd_start(sh->curr_cmd) == 1)
			return ;
		else
			exec_simple_pipe(sh);
	}
	else
		return ;
	safe_close_all_pipes(sh);
}

int	exec_pipe(t_shell *sh)
{
	t_cmd	*curr;
	pid_t	pid;
	int		status;
	int		last_cmd;

	curr = sh->cmd;
	status = 0;
	while (curr)
	{
		if (curr->next == NULL)
			last_cmd = 1;
		else
			last_cmd = 0;
		if (prepare_pipe_command(sh, curr) == -1)
			return (-1);
		if (last_cmd && if_cmd_builtin(sh))
		{
			status = exec_builtin_main(sh, curr);
			break ;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			return (1);
		}
		else if (pid == 0)
		{
			pipe_fork_child(sh, &sh->new_pipe, &sh->old_pipe, last_cmd);
			iteration_pipe(sh);
			exit(EXIT_FAILURE);
		}
		else
		{
			curr->pid = pid;
			pipe_for_parent(&sh->new_pipe, &sh->old_pipe);
		}
		curr = curr->next;
	}
	status = wait_for_allpid(pid);
	exec_exit_status(1, status);
	return (status);
}

// int	exec_pipe(t_shell *sh)
// {
// 	t_cmd	*curr;
// 	pid_t	pid;

// 	curr = sh->cmd;
// 	while (curr)
// 	{
// 		if (prepare_pipe_command(sh, curr) == -1)
// 			return (-1);
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			safe_close_all_pipes(sh);
// 			break ;
// 		}
// 		if (pid == 0)
// 		{
// 			pipe_fork_child(&sh->new_pipe, &sh->old_pipe, is_last_cmd(curr));
// 			iteration_pipe(sh);
// 			exit(EXIT_SUCCESS);
// 		}
// 		else
// 		{
// 			pipe_for_parent(&sh->new_pipe, &sh->old_pipe);
// 		}
// 		curr = curr->next;
// 	}
// 	// close_all_heredoc_fd(sh->cmd);
// 	return (wait_for_allpid(pid));
// }
