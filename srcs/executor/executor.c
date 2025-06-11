/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:41:13 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/06 15:20:24 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_exit_status(int mode, int new_status)
{
	static int	last_exit_status;

	last_exit_status = 0;
	if (mode == 1)
	{
		if (new_status == -1)
			new_status = EXIT_FAILURE;
		last_exit_status = new_status;
	}
	return (last_exit_status);
}

bool	executor(t_cmd *cmd, t_shell *shell)
{
	int	status;
	t_cmd *cmd_tmp;

	cmd_tmp = cmd;
	if (if_cmd_simple(cmd_tmp) == 1)
		status = exec_simple(cmd_tmp, shell->env);
	else if (if_cmd_simple(cmd_tmp) == 0)
	{
		//printf("here i am IN EXECUTOR , cmd is %s \n", cmd_tmp->cmd);
		status = exec_pipe(cmd_tmp, shell);
	}
	else
		status = -1;
	exec_exit_status(1, status);
	//cmd_tmp = cmd_tmp->next;
	//while (cmd_tmp != data->cmd)
	//{
		//while (cmp_tmp && exec_skip(cmd_tmp))
			//cmd_tmp = cmd_tmp->next;
		//if (cmd_tmp)
			//exec_set(exec(data, cmd_tmp));
	//}
	return (exec_exit_status(0, 0) == 0);
}

