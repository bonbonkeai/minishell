/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:28:32 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/02 18:16:16 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_simple_pipe(t_shell *sh)
{
	t_cmd	*curr;
	int		status;

	curr = sh->curr_cmd;
	status = 0;
	status = handle_preprecheck(curr);
	handle_check_prexec(sh, curr);
	exec_child(sh, curr, status);
	return (status);
}

void	touch_all_output_files_in_list(t_cmd *cmd_list)
{
	t_cmd	*curr;

	curr = cmd_list;
	while (curr)
	{
		touch_all_output_files(curr);
		curr = curr->next;
	}
}
