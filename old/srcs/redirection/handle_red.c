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

void	apply_input_red(t_shell *sh)
{
	int	fd;

	if (!sh->current_cmd->infile)
		return ;
	fd = open(sh->current_cmd->infile, O_RDONLY);
	if (fd < 0)
	{
		perror(sh->current_cmd->infile);
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

void	apply_output_red(t_shell *sh)
{
	int	fd;
	int	flags;

	if (!sh->current_cmd->outfile)
		return ;
	flags = O_WRONLY | O_CREAT;
	if (sh->current_cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(sh->current_cmd->outfile, flags, 0644);
	if (fd < 0)
	{
		perror(sh->current_cmd->outfile);
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

void	apply_red(t_shell *sh)
{
	if (sh->current_cmd->heredoc_fd != -1)
	{
		if (dup2(sh->current_cmd->heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc_fd");
			exit(EXIT_FAILURE);
		}
		close(sh->current_cmd->heredoc_fd);
	}
	else
		apply_input_red(sh);
	apply_output_red(sh);
}