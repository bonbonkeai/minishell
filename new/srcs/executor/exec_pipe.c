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


static int	exec_simple_pipe(t_shell *sh)
{
    t_cmd	*curr = sh->curr_cmd;
    int		status;

    if (!curr || !curr->cmd || curr->cmd[0] == '\0')
    {
        print_cmd_error("", "command not found");
        exit(127);
    }
    if (is_directory(curr->cmd))
    {
        print_cmd_error(curr->cmd, "Is a directory");
        exit(126);
    }
    if (if_cmd_builtin(sh) == 1)
    {
        // 内置命令直接执行，执行完exit退出子进程
        status = exec_builtin_main(sh);
        exit(status);
    }
    // 处理重定向
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
    // 执行外部命令
    status = execve_bin(sh);
    exit(status);
}

static void	iteration_pipe(t_shell *sh)
{
	if (!sh->curr_cmd)
		return ;
	// if ((if_cmd_start(sh)) == 1 || (if_cmd_simple(sh)) != 2)
	// {
	// 	if (if_cmd_start(sh) == 1)
	// 	{
	// 		printf("here i am WRONG!\n");
	// 		return ;
	// 	}
	if ((if_cmd_start(sh->curr_cmd)) == 1 || (if_cmd_simple(sh->curr_cmd)) != 2)
	{
		if (if_cmd_start(sh->curr_cmd) == 1)
		{
			printf("here i am WRONG!\n");
			return ;
		}
		else
			exec_simple_pipe(sh);
	}
	else
		return ;
	safe_close_all_pipes(sh);
}

int	exec_pipe(t_shell *sh)
{
	pid_t	pid;
	t_cmd *curr;
	int last_cmd;

	if (expand_heredoc_in_cmd_list(sh) != 0)
		return (-1);
	curr = sh->cmd;
	
	// t_cmd *tmp;
	// tmp = sh->cmd;
	// while(tmp)
	// {
	// 	ft_printf("A");
	// 	tmp = tmp->next;
	// }

	while (curr)
	{
		if (curr->next == NULL)
			last_cmd = 1;
		else
			last_cmd = 0;
		// ft_printf("%s\n", curr->cmd);
		sh->curr_cmd = curr;
		sh->new_pipe.fd[0] = -1;
		sh->new_pipe.fd[1] = -1;
		if (create_pipes(sh, curr) == -1)
			return (-1);
		pid = fork();
		// ft_printf("fork NUMBER\n");
		if (pid == -1)
		{
			safe_close_all_pipes(sh);
			break ;
		}
		if (pid == 0)
		{
			// pipe_fork_child(&sh->new_pipe, &sh->old_pipe);
			pipe_fork_child(&sh->new_pipe, &sh->old_pipe, last_cmd);
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