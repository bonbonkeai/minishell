/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:45:05 by jdu               #+#    #+#             */
/*   Updated: 2025/07/01 13:26:04 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_output_redir(char *op)
{
	return (ft_strcmp(op, ">") == 0 || ft_strcmp(op, ">>") == 0);
}

static bool	try_open_output_file(char *filename)
{
	int	fd;

	if (!filename)
		return (true);
	fd = open(filename, O_WRONLY | O_CREAT, 0644);
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
			if (!try_open_output_file(cmd->red[i + 1]))
				return (false);
			i++;
		}
		i++;
	}
	return (true);
}

/*bool	touch_all_output_files(t_cmd *cmd)
{
	int	fd;
	int	i;

	if (!cmd || !cmd->red)
		return (true);
	i = 0;
	while (cmd->red[i])
	{
		if (ft_strcmp(cmd->red[i], ">") == 0 \
		|| ft_strcmp(cmd->red[i], ">>") == 0)
		{
			if (cmd->red[i + 1])
			{
				fd = open(cmd->red[i + 1], O_WRONLY | O_CREAT, 0644);
				if (fd < 0)
				{
					perror(cmd->red[i + 1]);
					return (false);
				}
				else
					close(fd);
				i++;
			}
		}
		i++;
	}
	return (true);
}*/

int	count_redirs(char **red)
{
	int	len;

	len = 0;
	while (red && red[len])
		len++;
	return (len);
}

void safe_exit_with_io_close(t_shell *sh, int *storage, int code)
{
	if (storage)
		recover_io_and_close(storage);
	if (sh && sh->curr_cmd && sh->curr_cmd->heredoc_fd != -1)
		close(sh->curr_cmd->heredoc_fd);
	free_shell(sh);
	exit(code);
}
