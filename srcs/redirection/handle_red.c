/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                    +#+  +:+       +#+             */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:13:50 by jdu          #+#    #+#             	  */
/*   Updated: 2025/07/11 20:39:39 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_input_red(t_shell *sh, int *storage)
{
	int	fd;

	if (!sh || !sh->curr_cmd || !sh->curr_cmd->infile)
		return (0);
	fd = open(sh->curr_cmd->infile, O_RDONLY);
	if (sh->curr_cmd->is_dummy_cmd)
		return (safe_close(sh, storage), -1);
	if (fd < 0)
	{
		perror(sh->curr_cmd->infile);
		safe_close(sh, storage);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 stdin");
		close(fd);
		safe_close(sh, storage);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	open_output_file(t_shell *sh)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (sh->curr_cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (open(sh->curr_cmd->outfile, flags, 0644));
}

int	apply_output_red(t_shell *sh, int *storage)
{
	int	fd;

	if (!sh || !sh->curr_cmd || !sh->curr_cmd->outfile)
		return (0);
	fd = open_output_file(sh);
	if (sh->curr_cmd->is_dummy_cmd)
		return (close(fd), 0);
	if (fd < 0)
	{
		perror(sh->curr_cmd->outfile);
		safe_close(sh, storage);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 stdout");
		close(fd);
		safe_close(sh, storage);
		return (-1);
	}
	close(fd);
	return (0);
}

int	is_red_type(t_token_type type)
{
	return (type == T_INPUT || type == T_OUTPUT
		|| type == T_APPEND || type == T_HEREDOC);
}
