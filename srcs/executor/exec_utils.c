/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:33:59 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/02 21:05:28 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_cmd_builtin(t_shell *sh)
{
	int		re;
	t_cmd	*curr;

	re = 0;
	curr = sh->curr_cmd;
	if (!curr || !curr->cmd)
		return (0);
	if (ft_strncmp(curr->cmd, "cd", 3) == 0)
		re = 1;
	else if (ft_strncmp(curr->cmd, "echo", 5) == 0)
		re = 1;
	else if (ft_strncmp(curr->cmd, "env", 4) == 0)
		re = 1;
	else if (ft_strncmp(curr->cmd, "export", 7) == 0)
		re = 1;
	else if (ft_strncmp(curr->cmd, "pwd", 4) == 0)
		re = 1;
	else if (ft_strncmp(curr->cmd, "unset", 6) == 0)
		re = 1;
	else if (ft_strncmp(curr->cmd, "exit", 5) == 0)
		re = 1;
	return (re);
}

int	if_cmd_start(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "(") == 0)
		return (1);
	else
		return (0);
}

int	if_cmd_simple(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "(") != 0)
	{
		if (cmd->next == NULL)
			return (1);
		else
			return (0);
	}
	return (2);
}

void	exec_simple_exit(t_shell *sh)
{
	if (sh->cmd)
		free_cmd_list(sh->cmd);
}

void	close_all_heredoc_fd(t_cmd *cmd_list)
{
	t_cmd	*curr;

	curr = cmd_list;
	while (curr)
	{
		if (curr->heredoc_fd != -1)
		{
			close(curr->heredoc_fd);
			curr->heredoc_fd = -1;
		}
		curr = curr->next;
	}
}
