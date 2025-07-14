/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:41:13 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/13 21:13:52 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_exit_status(int mode, int new_status)
{
	static int	last_exit_status = 0;

	if (mode == 1)
	{
		if (new_status == -1)
			new_status = EXIT_FAILURE;
		last_exit_status = new_status;
	}
	return (last_exit_status);
}

int	handle_dummy_cmd(t_shell *sh, t_cmd *cmd)
{
	if (resolve_redir(sh, cmd, NULL) < 0)
		return (1);
	free(cmd->cmd);
	cmd->cmd = NULL;
	cmd->is_dummy_cmd = 0;
	return (0);
}

int	executor(t_shell *shell)
{
	int	status;

	if (!shell || !shell->cmd)
		return (true);
	if (!shell->cmd || (!shell->cmd->cmd && !shell->cmd->args && \
				(shell->cmd->heredoc || \
				shell->cmd->infile || shell->cmd->outfile)))
		return (0);
	shell->curr_cmd = shell->cmd;
	if (if_cmd_simple(shell->cmd) == 1)
		status = exec_simple(shell);
	else if (if_cmd_simple(shell->cmd) == 0)
		status = exec_pipe(shell);
	else
		status = -1;
	exec_exit_status(1, status);
	shell->status = exec_exit_status(0, 0);
	return (shell->status);
}

int	is_directory(const char *path)
{
	struct stat	st;
	int			len;

	if (!path)
		return (0);
	if (stat(path, &st) != 0 || !S_ISDIR(st.st_mode))
		return (0);
	len = ft_strlen(path);
	if (path[0] == '/')
		return (1);
	if (ft_strncmp(path, "./", 2) == 0)
		return (1);
	if (len > 0 && path[len - 1] == '/')
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
