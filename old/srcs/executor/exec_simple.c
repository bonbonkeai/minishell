/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:15:09 by jinhuang          #+#    #+#             */
/*   Updated: 2025/05/28 20:19:01 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/* int	exec_simple(t_shell *sh)
{
	int		pid;
	int		status;

	if (!sh->cmd || !sh->cmd->cmd || sh->cmd->cmd[0] == '\0')
	{
		print_cmd_error("", "command not found");
		return (127);
	}
	if (is_directory(sh->cmd->cmd))
	{
		print_cmd_error(sh->cmd->cmd, "Is a directory");
		return (126);
	}
	if (if_cmd_builtin(sh) == 1)
		return (exec_builtin_main(sh));

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (sh->cmd->heredoc_fd != -1)
		{
			if (dup2(sh->cmd->heredoc_fd, STDIN_FILENO) == -1)
			{
				perror("dup2 heredoc_fd");
				exit(EXIT_FAILURE);
			}
			close(sh->cmd->heredoc_fd);
		}
		else
			apply_input_red(sh); 

		apply_output_red(sh);
		status = execve_bin(sh);
		exit(status);
		// apply_red(sh);
		// status = execve_bin(sh);
		// exit(status);
	}
	else if (pid > 0)
	{
		sh->cmd->pid = pid;
		return (exec_wait_pid(pid));
	}
	else
	{
		perror("fork failed");
		return (1);
	}
	return (status);
}

int	execve_bin(t_shell *sh)
{
	char	*path;
	char	**arg;
	char	**vars;

	path = get_path(sh);
	arg = get_args(sh);
	vars = get_env_variables(sh);
	if (!path || access(path, X_OK) == -1)
	{
		if (is_directory(sh->cmd->cmd))
			print_cmd_error(sh->cmd->cmd, "Is a directory");
		else
			print_cmd_error(sh->cmd->cmd, "command not found");
		if (path == NULL)
			return (127);
		else
			return (126);
	}
	if (check_cmd_standard(sh))
	{
		if (access(path, X_OK) == -1)
		{
			perror("Permission denied or command not executable");
			return (2);
		}
		execve(path, arg, vars);
		perror("Command execution failed");
		return (1);
	}
	else
	{
		execve(path, arg, vars);
		perror("Command execution failed");
		return (1);
	}
} */

int	exec_simple(t_shell *sh)
{
	int		pid;
	int		status;
	t_cmd *curr = sh->current_cmd;

	//printf("heyhereexe\n");
	if (!curr || !curr->cmd || curr->cmd[0] == '\0')
	{
		print_cmd_error("", "command not found");
		return (127);
	}
	if (is_directory(curr->cmd))
	{
		print_cmd_error(curr->cmd, "Is a directory");
		return (126);
	}
	if (if_cmd_builtin(sh) == 1)
		return (exec_builtin_main(sh));
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		//fprintf(stderr, "[child %d] exec command: '%s'\n", getpid(), curr->cmd);
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
		//fprintf(stderr, "[child %d] execve_bin returned %d\n", getpid(), status);
		exit(status);
		// apply_red(sh);
		// status = execve_bin(sh);
		// exit(status);
	}
	else if (pid > 0)
	{
		sh->cmd->pid = pid;
		return (exec_wait_pid(pid));
	}
	else
	{
		perror("fork failed");
		return (1);
	}
	return (status);
}

int execve_bin(t_shell *sh)
{
	char *path;
	char **arg;
	char **vars;
	t_cmd *curr = sh->current_cmd;

	path = get_path(sh);
	arg = get_args(sh);
	vars = get_env_variables(sh);
	// fprintf(stderr, "[execve_bin] path: %s\n", path ? path : "NULL");
	// fprintf(stderr, "[execve_bin] args:");
	// if (arg)
	// {
	// 	for (int i = 0; arg[i] != NULL; i++)
	// 		fprintf(stderr, " '%s'", arg[i]);
	// 	fprintf(stderr, "\n");
	// }
	// else
	// {
	// 	fprintf(stderr, " NULL\n");
	// }

	if (!path || access(path, X_OK) == -1)
	{
		if (path == NULL)
		{
			print_cmd_error(curr->cmd, "No such file or directory");
			return (127);
		}
		else if (is_directory(curr->cmd))
			print_cmd_error(curr->cmd, "Is a directory");
		else
			print_cmd_error(curr->cmd, "command not found");
		return (126);
	}

	if (check_cmd_standard(sh))
	{
		if (access(path, X_OK) == -1)
		{
			perror("Permission denied or command not executable");
			return (2);
		}
		execve(path, arg, vars);
		perror("Command execution failed");
		return (1);
	}
	else
	{
		execve(path, arg, vars);
		perror("Command execution failed");
		return (1);
	}
}
