/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:45:07 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/12 20:56:27 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	allocate_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (builtin_cd(shell, cmd->args));
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (builtin_echo(cmd->args));
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		return (builtin_export(cmd->args, &shell->env));
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (builtin_unset(&shell->env, cmd->args));
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		return (builtin_env(shell->env));
	else
		return (1);
}

int	apply_store_and_red(t_cmd *cmd, int storage[2])
{
	if (ft_strcmp(cmd->cmd, "exit") != 0)
	{
		if (!save_std_io(storage)) 
		{
    			perror("Failed to save std IO");
    			return(1);
		}
		apply_red(cmd);
	}
	else
	{
		builtin_exit(cmd->args);
		return (-1);
	}
	return (0);
}

void	recover_io_and_close(int storage[2])
{
	bool	res;

	res = true;
	if (!restore_std_io(storage))
		res = false;
	if (storage[0] != -1)
	{
		close(storage[0]);
		storage[0] = -1;
	}
	if (storage[1] != -1)
	{
		close(storage[1]);
		storage[1] = -1;
	}
	if (!res)
		perror("restore error:");
}


int	exec_builtin_main(t_cmd *cmd, t_shell *shell)
{
	int	status;
	int	ret;
	int	storage[2] = {-1, -1};

	ret = apply_store_and_red(cmd, storage);
	if (ret == -1)
		return (0);
	status = allocate_builtin(cmd, shell);
	recover_io_and_close(storage);
	return (status);
}