/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:38:47 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/03 18:00:11 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	exec_new_shell(t_cmd *cmd, t_shell *shell)
{
	int	status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		pipe_fork_child(&shell->new_pipe, &shell->old_pipe);
		status = rediection(cmd, shell);
		if (status != 0)
			clean_shell(shell, cmd);
		cmd = cmd->next;
	}
	else if (pid == -1)
		error_raise_pipeline();
}
