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
