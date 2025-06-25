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

int	exec_simple(t_cmd *cmd, t_shell *shell)
{
	int		pid;
	int		status;

	if (!cmd || !cmd->cmd || cmd->cmd[0] == '\0')
	{
		print_cmd_error("", "command not found");
		return (127);
	}
	if (is_directory(cmd->cmd))
	{
		print_cmd_error(cmd->cmd, "Is a directory");
		return (126);
	}
	if (if_cmd_builtin(cmd) == 1)
		return (exec_builtin_main(cmd, shell));

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (cmd->heredoc_fd != -1)
		{
			if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
			{
				perror("dup2 heredoc_fd");
				exit(EXIT_FAILURE);
			}
			close(cmd->heredoc_fd);
		}
		else
			apply_input_red(cmd); 

		apply_output_red(cmd);
		status = execve_bin(cmd, shell->env);
		exit(status);
	}
	else if (pid > 0)
	{
		cmd->pid = pid;
		return (exec_wait_pid(pid));
	}
	else
	{
		perror("fork failed");
		return (1);
	}
	return (status);
}

int	execve_bin(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**arg;
	char	**vars;

	path = get_path(cmd, env);
	arg = get_args(cmd);
	vars = get_env_variables(env);
	if (!path || access(path, X_OK) == -1)
	{
		if (is_directory(cmd->cmd))
			print_cmd_error(cmd->cmd, "Is a directory");
		else
			print_cmd_error(cmd->cmd, "command not found");
		if (path == NULL)
			return (127);
		else
			return (126);
	}
	if (check_cmd_standard(cmd))
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
