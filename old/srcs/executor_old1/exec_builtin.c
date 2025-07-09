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
	if (ft_strcmp(shell->curr_cmd->cmd, "cd") == 0)
		return (builtin_cd(shell, shell->curr_cmd->args));
	else if (ft_strcmp(shell->curr_cmd->cmd, "echo") == 0)
		return (builtin_echo(shell->curr_cmd->args));
	else if (ft_strcmp(shell->curr_cmd->cmd, "pwd") == 0)
		return (builtin_pwd(shell));
	else if (ft_strcmp(shell->curr_cmd->cmd, "export") == 0)
		return (builtin_export(shell->curr_cmd->args, shell));
	else if (ft_strcmp(shell->curr_cmd->cmd, "unset") == 0)
		return (builtin_unset(shell, shell->curr_cmd->args));
	else if (ft_strcmp(shell->curr_cmd->cmd, "env") == 0)
		return (builtin_env(shell));
	else
		return (1);
}

// int	apply_store_and_red(t_shell *sh, int storage[2])
// {
// 	if (ft_strcmp(sh->cmd->cmd, "exit") != 0)
// 	{
// 		if (!save_std_io(storage)) 
// 		{
//     			perror("Failed to save std IO");
//     			return(1);
// 		}
// 		apply_red(sh);
// 	}
// 	else
// 	{
// 		builtin_exit(sh->cmd->args);
// 		return (-1);
// 	}
// 	return (0);
// }

int	apply_store_and_red(t_shell *sh, int storage[2])
{
	if (ft_strcmp(sh->curr_cmd->cmd, "exit") != 0)
	{
		if (!save_std_io(storage)) 
		{
    			perror("Failed to save std IO");
				recover_io_and_close(storage);
    			return (1);
		}
		apply_red(sh);
	}
	else
	{
		// recover_io_and_close(storage);
		builtin_exit(sh, sh->curr_cmd->args);
		// builtin_exit(sh->curr_cmd->args);
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
		fprintf(stderr, "🔧 closing storage[0] = %d\n", storage[0]);
		close(storage[0]);
		storage[0] = -1;
	}
	if (storage[1] != -1)
	{
		fprintf(stderr, "🔧 closing storage[1] = %d\n", storage[1]);
		close(storage[1]);
		storage[1] = -1;
	}
	if (!res)
		perror("restore error:");
}


// int	exec_builtin_main(t_shell *sh)
// {
// 	int	status;
// 	int	ret;
// 	int	storage[2] = {-1, -1};

// 	//
// 	sh->curr_cmd = sh->cmd;
// 	//ft_fprintf(2, "[DEBUG] entering exec_builtin_main for cmd: %s\n", sh->cmd->cmd);
// 	//
// 	ret = apply_store_and_red(sh, storage);
// 	if (ret == -1)
// 		return (0);
// 	status = allocate_builtin(sh);
// 	recover_io_and_close(storage);
// 	// free_shell(sh);
// 	return (status);
// }

int	exec_builtin_main(t_shell *sh)
{
	int	status;
	int	storage[2] = {-1, -1};

	sh->curr_cmd = sh->cmd;
	if (!sh->curr_cmd || !sh->curr_cmd->cmd)
		return (0);
	if (ft_strcmp(sh->curr_cmd->cmd, "exit") == 0)
		builtin_exit(sh, sh->curr_cmd->args);
	printf("here_debug0\n");
	ret = apply_store_and_red(sh, storage);
	printf("here_debug1\n");
	if (ret != 0)
	{
		recover_io_and_close(storage);
		return (0);
	}
	if (!touch_all_output_files(sh->curr_cmd))
	{
		safe_exit_with_io_close(sh, storage, 1);
		printf("here_debug2\n");
	}
	printf("here_debug3\n");
	resolve_redir(sh, sh->curr_cmd, storage);
	printf("here_debug4\n");
	status = allocate_builtin(sh);
	recover_io_and_close(storage);
	return (status);
}
