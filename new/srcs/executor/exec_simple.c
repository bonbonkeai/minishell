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


int	exec_simple(t_shell *sh)
{
	int		pid;
	int		status;
	t_cmd *curr;
	
	curr = sh->curr_cmd;

	//
	if (!curr || (!curr->cmd && !curr->args && curr->heredoc))
		return (0);
	//
	if (!curr || !curr->cmd || curr->cmd[0] == '\0')
	{
		print_cmd_error(curr->cmd, "command not found");
		return (127);
	}
	if (is_empty_command(sh->trimmed_prompt))
    {
		print_cmd_error(sh->trimmed_prompt, "command not found");
		// print_cmd_error(curr->cmd, "command not found");
		return (127);
    }
	if (is_directory(curr->cmd))
	{
		print_cmd_error(curr->cmd, "Is a directory");
		return (126);
	}
	if (if_cmd_builtin(sh) == 1)
	{
		touch_all_output_files(curr);
		resolve_redir(curr);
		return (exec_builtin_main(sh));
	}
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		touch_all_output_files(curr);
    	resolve_redir(curr);
		signal_default();
		if (curr->heredoc_fd != -1)
		{
			if (dup2(curr->heredoc_fd, STDIN_FILENO) == -1)
			{
				ft_fprintf(2, "dup2 heredoc_fd");
				exit(EXIT_FAILURE);
			}
			close(curr->heredoc_fd);
		}
		else
			apply_input_red(sh); 
		apply_output_red(sh);
		status = execve_bin(sh);
		//
		// if (sh->curr_cmd)
		// {
		// 	free_cmd(sh->curr_cmd);
		// 	sh->curr_cmd = NULL;
		// }
		//
		exit(status);
	}
	else if (pid > 0)
	{
		// sh->cmd->pid = pid;
		curr->pid = pid;
		return (exec_wait_pid(pid));
	}
	else
	{
		ft_fprintf(2, "fork failed");
		return (1);
	}
	return (status);
}

int	execve_bin(t_shell *sh)
{
	char	*path;
	char	**arg;
	char	**vars;
	t_cmd *curr;

	curr = sh->curr_cmd;
	path = get_path(sh);
	if (!path)
	{
		print_cmd_error(curr->cmd, "command not found");
		free_shell(sh);
		return (127);
	}
	arg = get_args(sh);
	if (!arg)
		return (free(path), 127);
	vars = get_env_variables(sh);
	if (!vars)
		return (free(path), free_paths(arg), 127);
	if (check_cmd_standard(sh))
	{
		if (access(path, X_OK) == -1)
		{
			ft_fprintf(2, "Permission denied or command not executable");
			return (2);
		}
		// execve(path, arg, vars);
		//
		if (execve(path, arg, vars) == -1)
		{
			ft_fprintf(2, "execve");
			free(path);
			free_paths(arg);
			free_paths(vars);
			return (EXIT_FAILURE);
		}
		//
		ft_fprintf(2, "Command execution failed");
		return (1);
	}
	else
	{
		execve(path, arg, vars);
		ft_fprintf(2, "Command execution failed");
		return (1);
	}
}
