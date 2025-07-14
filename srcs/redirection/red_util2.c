/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:45:05 by jdu               #+#    #+#             */
/*   Updated: 2025/07/11 20:42:08 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_output_redir(char *op)
{
	return (ft_strcmp(op, ">") == 0 || ft_strcmp(op, ">>") == 0);
}

bool	try_open_output_file(char *op, char *filename)
{
	int	fd;
	int	flags;

	if (!filename)
		return (true);
	flags = O_WRONLY | O_CREAT;
	if (!ft_strcmp(op, ">"))
		flags |= O_TRUNC;
	else if (!ft_strcmp(op, ">>"))
		flags |= O_APPEND;
	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		perror(filename);
		return (false);
	}
	close(fd);
	return (true);
}

bool	touch_all_output_files(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->red)
		return (true);
	i = 0;
	while (cmd->red[i])
	{
		if (is_output_redir(cmd->red[i]))
		{
			if (!try_open_output_file(cmd->red[i], cmd->red[i + 1]))
				return (false);
			i++;
		}
		i++;
	}
	return (true);
}

bool	touch_all_output_files_red(t_cmd *cmd, int i)
{
	if (!cmd || !cmd->red)
		return (true);
	if (is_output_redir(cmd->red[i]))
	{
		if (!try_open_output_file(cmd->red[i], cmd->red[i + 1]))
			return (false);
	}
	return (true);
}

void	safe_close(t_shell *sh, int *storage)
{
	if (storage)
		recover_io_and_close(storage);
	if (sh && sh->curr_cmd && sh->curr_cmd->heredoc_fd != -1)
		close(sh->curr_cmd->heredoc_fd);
}
