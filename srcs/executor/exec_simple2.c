/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:52:08 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/11 20:25:35 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_dot_commands(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, ".") == 0)
	{
		print_cmd_error(cmd->cmd, "filename argument required");
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
		return (2);
	}
	if (ft_strcmp(cmd->cmd, "..") == 0)
	{
		print_cmd_error(cmd->cmd, "command not found");
		return (127);
	}
	return (-1);
}

int	handle_check_prexec(t_shell *sh, t_cmd *curr)
{
	int	ret;

	if (!curr || (!curr->cmd && !curr->args && curr->heredoc))
		return (0);
	if ((!curr->cmd || curr->cmd[0] == '\0') && !curr->red)
		return (0);
	if (is_empty_command(sh->trimmed_prompt))
	{
		print_cmd_error(sh->trimmed_prompt, "command not found");
		return (127);
	}
	ret = handle_dot_commands(curr);
	if (ret != -1)
		return (ret);
	if (is_directory(curr->cmd))
	{
		print_cmd_error(curr->cmd, "Is a directory");
		return (126);
	}
	return (-1);
}
