/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:44:57 by jdu               #+#    #+#             */
/*   Updated: 2025/07/01 21:26:16 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_input_redir(t_cmd *cmd, char *op, char *file)
{
	if (!op || !file || !cmd)
		return ;
	if (!ft_strcmp(op, "<"))
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup(file);
	}
}

void	handle_output_redir(t_cmd *cmd, char *op, char *file)
{
	char	*tmp;

	if (!cmd || !op || !file)
		return ;
	tmp = ft_strdup(file);
	if (!tmp)
		return ;
	if (!ft_strcmp(op, ">"))
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = tmp;
		cmd->append = 0;
	}
	else if (!ft_strcmp(op, ">>"))
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = tmp;
		cmd->append = 1;
	}
}

void	process_input_redir(t_shell *sh, char *op, char *file, int *storage)
{
	t_cmd *cmd;
	
	cmd = sh->curr_cmd;
	if (!ft_strcmp(op, "<") && cmd->heredoc_fd != 1)
	{
		handle_input_redir(cmd, op, file);
		apply_input_red(sh, storage);
	}
}

void	apply_heredoc_fd(t_shell *sh, t_cmd *cmd, int *storage)
{
	if (cmd->heredoc_fd == -1)
		return ;
	if (cmd->heredoc_fd != -1)
	{
		if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc_fd");
			safe_exit_with_io_close(sh, storage, EXIT_FAILURE);
		}
		// ft_printf("HERE fd: %d\n", cmd->heredoc_fd);
		// close_all_heredoc_fd(sh->cmd);
		// close(cmd->heredoc_fd);
		// cmd->heredoc_fd = -1;
	}
}
// void	apply_heredoc_fd(t_shell *sh, t_cmd *cmd, int *storage)
// {
// 	if (cmd->heredoc_fd == -1)
// 		return ;
// 	if (cmd->heredoc_fd != -1)
// 	{
// 		if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 heredoc_fd");
// 			safe_exit_with_io_close(sh, storage, EXIT_FAILURE);
// 		}
// 		close(cmd->heredoc_fd);
// 		cmd->heredoc_fd = -1;
// 	}
// }

// void	resolve_redir(t_shell *sh, t_cmd *cmd, int *storage)
// {
// 	int		i;
// 	char	*op;
// 	char	*file;

// 	if (!cmd || !cmd->red)
// 		return ;
// 	if (cmd->heredoc_fd != -1)
// 		apply_heredoc_fd(sh, cmd, storage);
// 	else
// 	{
// 		i = 0;
// 		while (cmd->red[i] && cmd->red[i + 1])
// 		{
// 			op = cmd->red[i];
// 			file = cmd->red[i + 1];
// 			if (cmd->heredoc_fd == -1 && !ft_strcmp(op, "<"))
// 			{
// 				handle_input_redir(cmd, op, file);
// 				apply_input_red(sh, storage);
// 			}
// 			i += 2;
// 		}
// 	}
// 	i = 0;
// 	while (cmd->red[i] && cmd->red[i + 1])
// 	{
// 		op = cmd->red[i];
// 		file = cmd->red[i + 1];
// 		if (!ft_strcmp(op, ">") || !ft_strcmp(op, ">>"))
// 		{
// 			if (!touch_all_output_files(cmd))
// 				safe_exit_with_io_close(sh, storage, 1);
// 			handle_output_redir(cmd, op, file);
// 		}
// 		i += 2;
// 	}
// 	apply_output_red(sh, storage);
// }


void	resolve_redir(t_shell *sh, t_cmd *cmd, int *storage)
{
	int		i;
	char	*op;
	char	*file;
	
	if (!cmd || !cmd->red)
		return ;
	//
	sh->curr_cmd = cmd;
	//
	i = 0;
	while (cmd->red[i] && cmd->red[i + 1])
	{
		op = cmd->red[i];
		file = cmd->red[i + 1];
		process_input_redir(sh, op, file, storage);
		if (!ft_strcmp(op, ">") || !ft_strcmp(op, ">>"))
		{
			if (!touch_all_output_files(cmd))
				safe_exit_with_io_close(sh, storage, 1);
			handle_output_redir(cmd, op, file);
		}
		i += 2;
	}
	apply_heredoc_fd(sh, cmd, storage);
	apply_output_red(sh, storage);
}

// void	resolve_redir(t_shell *sh, t_cmd *cmd, int *storage)
// {
// 	int		i;
// 	char	*op;
// 	char	*file;

// 	i = 0;
// 	if (!cmd || !cmd->red)
// 		return ;
// 	while (cmd->red[i] && cmd->red[i + 1])
// 	{
// 		op = cmd->red[i];
// 		file = cmd->red[i + 1];
// 		if (!ft_strcmp(op, "<") && cmd->heredoc_fd != 1)
// 		{
// 			handle_input_redir(cmd, op, file);
// 			apply_input_red(sh);
// 		}
// 		else if (!ft_strcmp(op, ">") || !ft_strcmp(op, ">>"))
// 		{
// 			if (!touch_all_output_files(cmd))
// 			{
// 				safe_exit_with_io_close(sh, storage, 1);
// 			}
// 			handle_output_redir(cmd, op, file);
// 		}
// 		i += 2;
// 	}
// 	if (cmd->heredoc_fd != -1)
// 	{
// 		if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 heredoc_fd");
// 			safe_exit_with_io_close(sh, storage, EXIT_FAILURE);
// 		}
// 		close(cmd->heredoc_fd);
// 	}
// 	apply_output_red(sh);
// }
