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

int	exec_simple(t_cmd *cmd, t_env *env)
{
	int		pid;
	int		status;

	if (if_cmd_builtin(cmd) == 1)
		return (0);
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		status = execve_bin(cmd, env);
		exec_simple_exit(cmd);
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
	int		re;

	re = 0;
	path = get_path(cmd, env);
	arg = get_args(cmd);
	vars = get_env_variables(env);
	//printf("HEYYY SIMPLE\n");
	if (check_cmd_standard(cmd))
	{
		//printf("HEREEEEE\n");
		int i = 0;
		while (arg && arg[i]) {
    		//printf("arg[%d] = %s\n", i, arg[i]);
			//printf("path = %s \n", path);
    		i++;
		}
		if (access(path, X_OK) == -1) 
		{
    		perror("Permission denied or command not executable");
    		return (2);
		}
		execve(path, arg, vars);
		perror("Command failure : ");
		re = 1;
	}
	else
	{
		//printf("HEYYYYY\n");
		apply_red(cmd);
		printf("HEYYYYY2222\n");
		//if (arg[1] == "\"Fri\"")
		//arg[1] = "Fri";	
		int	i = 0;
		while (arg && arg[i]) {
    	printf("arg[%d] = %s\n", i, arg[i]);
    	i++;
		}
		execve(path, arg, vars);
		perror("Command failure : ");
		re = 1;
	}
	return (re);
}

