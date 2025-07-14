/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:44:57 by jdu               #+#    #+#             */
/*   Updated: 2025/07/11 20:41:48 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_output_op(char *op)
{
	return (!ft_strcmp(op, ">") || !ft_strcmp(op, ">>"));
}

// static bool	handle_redir_pair(t_shell *sh, 
// t_cmd *cmd, char *op, char *file, int *storage)
// {
// 	process_input_redir(sh, op, file);
// 	if (apply_input_red(sh, storage) < 0)
// 		return (false);
// 	if (is_output_op(op))
// 	{
// 		if (!touch_all_output_files(cmd))
// 		{
// 			safe_close(sh, storage);
// 			return (false);
// 		}
// 		handle_output_redir(cmd, op, file);
// 	}
// 	return (true);
// }

// static int	handle_all_redirections(t_shell *sh, t_cmd *cmd, int *storage)
// {
// 	int		i;
// 	char	*op;
// 	char	*file;

// 	i = 0;
// 	while (cmd->red[i] && cmd->red[i + 1])
// 	{
// 		op = cmd->red[i];
// 		file = cmd->red[i + 1];
// 		if (!handle_redir_pair(sh, cmd, op, file, storage))
// 			return (-1);
// 		i += 2;
// 	}
// 	return (0);
// }

static int	handle_all_redirections(t_shell *sh, t_cmd *cmd, int *storage)
{
	int		i;
	char	*op;
	char	*file;

	i = 0;
	while (cmd->red[i] && cmd->red[i + 1])
	{
		op = cmd->red[i];
		file = cmd->red[i + 1];
		process_input_redir(sh, op, file);
		if (apply_input_red(sh, storage) < 0)
			return (-1);
		if (is_output_op(op))
		{
			if (!touch_all_output_files_red(cmd, i))
			{
				safe_close(sh, storage);
				return (-1);
			}
			handle_output_redir(cmd, op, file);
		}
		i += 2;
	}
	return (0);
}

// static int	handle_all_redirections(t_shell *sh, t_cmd *cmd, int *storage)
// {
// 	int		i;
// 	char	*op;
// 	char	*file;

// 	i = 0;
// 	while (cmd->red[i] && cmd->red[i + 1])
// 	{
// 		// if (cmd->red)
// 		// {
// 		// 	for (int j = 0; cmd->red[j] != NULL; j++)
// 		// 		fprintf(stdout, "cmd->red[%d]: %s\n", j, cmd->red[j]);
// 		// }
// 		op = cmd->red[i];
// 		file = cmd->red[i + 1];
// 		fprintf(stdout, "cmd->red[%d]: %s\n",i, cmd->red[i]);
// 		process_input_redir(sh, op, file);
// 		fprintf(stdout, "cmd->red[%d]: %s\n",i, cmd->red[i]);
// 		if (apply_input_red(sh, storage) < 0)
// 		{
// 			//printf("here1\n");
// 			return (-1);
// 		}
// 		fprintf(stdout, "cmd->red[%d]: %s\n",i, cmd->red[i]);
// 		if (is_output_op(op))
// 		{
// 			if (!touch_all_output_files(cmd))
// 			{
// 				//printf("here2\n");
// 				safe_close(sh, storage);
// 				return (-1);
// 			}
// 			handle_output_redir(cmd, op, file);
// 		}
// 		fprintf(stdout, "cmd->red[%d]: %s\n",i, cmd->red[i]);
// 		i += 2;
// 	}
// 	return (0);
// }

int	resolve_redir(t_shell *sh, t_cmd *cmd, int *storage)
{
	if (!cmd || !cmd->red)
		return (0);
	sh->curr_cmd = cmd;
	if (handle_all_redirections(sh, cmd, storage) < 0)
		return (-1);
	if (apply_heredoc_fd(sh, cmd, storage) < 0)
		return (-1);
	if (apply_input_red(sh, storage) < 0)
		return (-1);
	if (apply_output_red(sh, storage) < 0)
		return (-1);
	return (0);
}

// int resolve_redir(t_shell *sh, t_cmd *cmd, int *storage)
// {
// 	int		i;
// 	char	*op;
// 	char	*file;

// 	if (!cmd || !cmd->red)
// 		return (0);
// 	sh->curr_cmd = cmd;
// 	i = 0;
// 	while (cmd->red[i] && cmd->red[i + 1])
// 	{
// 		op = cmd->red[i];
// 		file = cmd->red[i + 1];
// 		process_input_redir(sh, op, file);
//         if (apply_input_red(sh, storage) < 0)
// 		    return (-1);
// 		if (!ft_strcmp(op, ">") || !ft_strcmp(op, ">>"))
// 		{
// 			if (!touch_all_output_files(cmd))
// 			{
// 				safe_close(sh, storage);
// 				return (-1);
// 			}
// 			handle_output_redir(cmd, op, file);
// 		}
// 		i += 2;
// 	}
// 	if (apply_heredoc_fd(sh, cmd, storage) < 0)
// 		return (-1);
// 	if (apply_input_red(sh, storage) < 0)
// 		return (-1);
// 	if (apply_output_red(sh, storage) < 0)
// 		return (-1);
// 	return (0);
// }
