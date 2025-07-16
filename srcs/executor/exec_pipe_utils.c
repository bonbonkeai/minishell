/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:28:32 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/13 19:37:29 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_check(t_shell *sh, t_cmd *curr)
{
	if ((!curr || !curr->cmd || curr->cmd[0] == '\0') && !curr->red)
	{
		print_cmd_error(curr->cmd, "command not found");
		free_shell(sh);
		exit (127);
	}
	if (is_empty_command(sh->trimmed_prompt))
	{
		print_cmd_error(sh->trimmed_prompt, "command not found");
		free_shell(sh);
		exit (127);
	}
	if (is_directory(curr->cmd))
	{
		print_cmd_error(curr->cmd, "Is a directory");
		free_shell(sh);
		exit (126);
	}
}

int	exec_simple_pipe(t_shell *sh)
{
	t_cmd	*curr;
	int		status;

	curr = sh->curr_cmd;
	handle_check(sh, curr);
	status = check_exec_if_builtin(sh, curr);
	if (status != -1)
		return (status);
	exec_child(sh, curr, status);
	return (status);
}

int	prepare_pipe_command(t_shell *sh, t_cmd *curr)
{
	sh->curr_cmd = curr;
	sh->new_pipe.fd[0] = -1;
	sh->new_pipe.fd[1] = -1;
	if (curr->next)
	{
		if (pipe(sh->new_pipe.fd) == -1)
		{
			perror("pipe failed");
			return (-1);
		}
	}
	return (0);
}

bool	is_last_cmd(t_cmd *cmd)
{
	if (cmd->next == NULL)
		return (1);
	else
		return (0);
}

int	command_num(t_cmd *cmd)
{
	t_cmd		*curr_count;
	int			command_count;

	curr_count = cmd;
	command_count = 0;
	while (curr_count)
	{
		command_count++;
		curr_count = curr_count->next;
	}
	return (command_count);
}
