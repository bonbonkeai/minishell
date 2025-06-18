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

// int	exec_simple(t_cmd *cmd, t_env *env)
// {
// 	int		pid;
// 	int		status;

// 	if (if_cmd_builtin(cmd) == 1)
// 		return (exec_builtin_main(cmd, shell));
// 	status = 0;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		status = execve_bin(cmd, env);
// 		exec_simple_exit(cmd);
// 	}
// 	else if (pid > 0)
// 	{
// 		cmd->pid = pid;
// 		return (exec_wait_pid(pid));
// 	}
// 	else
// 	{
// 		perror("fork failed");
// 		return (1);
// 	}
// 	return (status);
// }

// int	exec_simple(t_cmd *cmd, t_shell *shell)
// {
// 	int		pid;
// 	int		status;

// 	if (if_cmd_builtin(cmd) == 1)
// 		return (exec_builtin_main(cmd, shell));
// 	status = 0;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		status = execve_bin(cmd, shell->env);
// 		exec_simple_exit(cmd);
// 	}
// 	else if (pid > 0)
// 	{
// 		cmd->pid = pid;
// 		return (exec_wait_pid(pid));
// 	}
// 	else
// 	{
// 		perror("fork failed");
// 		return (1);
// 	}
// 	return (status);
// }

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
		// apply_red(cmd, shell->env);
		status = execve_bin(cmd, shell->env);
		exit(status);
		// exec_simple_exit(cmd);
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

// int	execve_bin(t_cmd *cmd, t_env *env)
// {
// 	char	*path;
// 	char	**arg;
// 	char	**vars;

// 	path = get_path(cmd, env);
// 	arg = get_args(cmd);
// 	vars = get_env_variables(env);

// 	if (!path || access(path, X_OK) == -1)
// 	{
// 		if (is_directory(cmd->cmd))
// 			print_cmd_error(cmd->cmd, "Is a directory");
// 		else
// 			print_cmd_error(cmd->cmd, "command not found");
// 		return ((path == NULL) ? 127 : 126);
// 	}
// 	execve(path, arg, vars);
// 	if (is_directory(path))
// 		print_cmd_error(path, "Is a directory");
// 	else
// 		print_cmd_error(cmd->cmd, "command not found");
// 	return (127);
// }


int	execve_bin(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**arg;
	char	**vars;
	int		re;

	re = 0;
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
		re = 1;
	}
	else
	{
		apply_red(cmd, env);
		execve(path, arg, vars);
		// perror("Command execution failed");
		if (is_directory(path))
			print_cmd_error(path, "Is a directory");
		else
			print_cmd_error(cmd->cmd, "command not found");
		re = 1;
	}
	return (re);
}
