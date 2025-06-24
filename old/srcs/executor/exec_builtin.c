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

int	allocate_builtin(t_shell *shell)
{
	if (ft_strcmp(shell->current_cmd->cmd, "cd") == 0)
		return (builtin_cd(shell, shell->current_cmd->args));
	else if (ft_strcmp(shell->current_cmd->cmd, "echo") == 0)
		return (builtin_echo(shell->current_cmd->args));
	else if (ft_strcmp(shell->current_cmd->cmd, "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(shell->current_cmd->cmd, "export") == 0)
		return (builtin_export(shell->current_cmd->args, shell));
	else if (ft_strcmp(shell->current_cmd->cmd, "unset") == 0)
		return (builtin_unset(shell, shell->current_cmd->args));
	else if (ft_strcmp(shell->current_cmd->cmd, "env") == 0)
		return (builtin_env(shell));
	else
		return (1);
}

int	apply_store_and_red(t_shell *sh, int storage[2])
{
	if (ft_strcmp(sh->current_cmd->cmd, "exit") != 0)
	{
		if (!save_std_io(storage)) 
		{
    			perror("Failed to save std IO");
    			return(1);
		}
		apply_red(sh);
	}
	else
	{
		builtin_exit(sh->current_cmd->args);
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

int	exec_builtin_main(t_shell *sh)
{
	int	status;
	int	ret;
	int	storage[2] = {-1, -1};

	ret = apply_store_and_red(sh, storage);
	if (ret == -1)
		return (0);
	status = allocate_builtin(sh);
	recover_io_and_close(storage);
	return (status);
}