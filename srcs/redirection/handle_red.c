/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:13:50 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/01 21:27:13 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	apply_input_red(t_shell *sh)
// {
// 	int	fd;

// 	if (!sh->curr_cmd->infile)
// 		return ;
// 	fd = open(sh->curr_cmd->infile, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror(sh->curr_cmd->infile);
// 		// free_shell(sh);
// 		// exit(EXIT_FAILURE);
// 		safe_exit_with_io_close(sh, NULL, EXIT_FAILURE);
// 	}
// 	if (dup2(fd, STDIN_FILENO) == -1)
// 	{
// 		perror("dup2 stdin");
// 		close(fd);
// 		// exit(EXIT_FAILURE);
// 		safe_exit_with_io_close(sh, NULL, EXIT_FAILURE);
// 	}
// 	close(fd);
// }

void	apply_input_red(t_shell *sh, int *storage)
{
	int	fd;

	if (!sh->curr_cmd->infile)
		return ;
	fd = open(sh->curr_cmd->infile, O_RDONLY);
	if (fd < 0)
	{
		perror(sh->curr_cmd->infile);
		safe_exit_with_io_close(sh, storage, EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 stdin");
		close(fd);
		safe_exit_with_io_close(sh, storage, EXIT_FAILURE);
	}
	close(fd);
}

void	apply_output_red(t_shell *sh, int *storage)
{
	int	fd;
	int	flags;

	if (!sh->curr_cmd->outfile)
		return ;
	// ft_printf("No return\n");
	flags = O_WRONLY | O_CREAT;
	if (sh->curr_cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(sh->curr_cmd->outfile, flags, 0644);
	if (fd < 0)
	{
		perror(sh->curr_cmd->outfile);
		safe_exit_with_io_close(sh, storage, EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 stdout");
		close(fd);
		safe_exit_with_io_close(sh, storage, EXIT_FAILURE);
	}
	close(fd);
}

// void	apply_output_red(t_shell *sh)
// {
// 	int	fd;
// 	int	flags;

// 	if (!sh->curr_cmd->outfile)
// 		return ;
// 	flags = O_WRONLY | O_CREAT;
// 	if (sh->curr_cmd->append)
// 		flags |= O_APPEND;
// 	else
// 		flags |= O_TRUNC;
// 	fd = open(sh->curr_cmd->outfile, flags, 0644);
// 	if (fd < 0)
// 	{
// 		perror(sh->curr_cmd->outfile);
// 		// free_shell(sh);
// 		// exit(EXIT_FAILURE);
// 		safe_exit_with_io_close(sh, NULL, EXIT_FAILURE);
// 	}
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		perror("dup2 stdout");
// 		// free_shell(sh);
// 		close(fd);
// 		// exit(EXIT_FAILURE);
// 		safe_exit_with_io_close(sh, NULL, EXIT_FAILURE);
// 	}
// 	close(fd);
// }

int	is_red_type(t_token_type type)
{
	return (type == T_INPUT || type == T_OUTPUT
		|| type == T_APPEND || type == T_HEREDOC);
}
