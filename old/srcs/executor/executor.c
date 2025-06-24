/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:41:13 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/06 15:20:24 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_exit_status(int mode, int new_status)
{
	static int	last_exit_status;

	last_exit_status = 0;
	if (mode == 1)
	{
		if (new_status == -1)
			new_status = EXIT_FAILURE;
		last_exit_status = new_status;
	}
	return (last_exit_status);
}


bool	executor(t_shell *shell)
{
	int	status;

	shell->current_cmd = shell->cmd;
	if (if_cmd_simple(shell->cmd) == 1)
		status = exec_simple(shell);
	else if (if_cmd_simple(shell->cmd) == 0)
		status = exec_pipe(shell);
	else
		status = -1;
	exec_exit_status(1, status);
	shell->status = exec_exit_status(0, 0); 
	return (shell->status == 0);
}

int	is_directory(const char *path)
{
	struct stat st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

void	print_cmd_error(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd && cmd[0] != '\0')
		ft_putstr_fd(cmd, 2);
	else
		ft_putstr_fd(":", 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}