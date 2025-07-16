/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:44:57 by jdu               #+#    #+#             */
/*   Updated: 2025/07/16 14:11:48 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_output_op(char *op)
{
	return (!ft_strcmp(op, ">") || !ft_strcmp(op, ">>"));
}

static int	hendle_red_while(t_shell *sh, t_cmd *cmd, int *storage, int i)
{
	char	*op;
	char	*file;

	while (cmd->red[i] && cmd->red[i + 1])
	{
		op = cmd->red[i];
		file = cmd->red[i + 1];
		if (!ft_strcmp(op, "<") || !ft_strcmp(op, "<<"))
		{	
			if (handle_input_redir(cmd, op, file) < 0)
				return (safe_close(sh, storage), -1);
		}
		if (is_output_op(op))
		{
			if (!touch_all_output_files_red(cmd, i))
				return (safe_close(sh, storage), -1);
			if (handle_output_redir(cmd, op, file) < 0)
				return (safe_close(sh, storage), -1);
			if (apply_output_red(sh, storage) < 0)
				return (-1);
		}
		i += 2;
	}
	return (0);
}

static int	handle_all_redirections(t_shell *sh, t_cmd *cmd, int *storage)
{
	int		i;

	i = 0;
	if (hendle_red_while(sh, cmd, storage, i) < 0)
		return (-1);
	if (input_red(sh, cmd, storage) < 0)
		return (-1);
	return (0);
}

int	resolve_redir(t_shell *sh, t_cmd *cmd, int *storage)
{
	if (!cmd || !cmd->red)
		return (0);
	sh->curr_cmd = cmd;
	if (handle_all_redirections(sh, cmd, storage) < 0)
		return (-1);
	return (0);
}
