/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:13:50 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/03 21:39:03 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_input_red(t_cmd *cmd)
{
	int	fd;

	if (!cmd->infile)
		return ;
	fd = open(cmd->infile, O_RDONLY);
	if (fd < 0)
	{
		perror(cmd->infile);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 stdin");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	apply_output_red(t_cmd *cmd)
{
	int	fd;
	int	flags;

	if (!cmd->outfile)
		return ;
	flags = O_WRONLY | O_CREAT;
	if (cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->outfile, flags, 0644);
	if (fd < 0)
	{
		perror(cmd->outfile);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 stdout");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	apply_red(t_cmd *cmd)
{
	if (cmd->heredoc_fd != -1)
	{
		if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc_fd");
			exit(EXIT_FAILURE);
		}
		close(cmd->heredoc_fd);
	}
	else
		apply_input_red(cmd);
	apply_output_red(cmd);
}