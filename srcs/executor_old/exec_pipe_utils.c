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

// int	exec_simple_pipe(t_shell *sh)
// {
// 	t_cmd	*curr;
// 	int		status;

// 	curr = sh->curr_cmd;
// 	status = 0;
// 	status = handle_preprecheck(curr);
// 	handle_check_prexec(sh, curr);
// 	exec_child(sh, curr, status);
// 	return (status);
// }

 int	exec_simple_pipe(t_shell *sh)
{
    t_cmd	*curr = sh->curr_cmd;
    int		status;

    if (!curr || !curr->cmd || curr->cmd[0] == '\0')
    {
        print_cmd_error("", "command not found");
        exit(127);
    }
    if (is_directory(curr->cmd))
    {
        print_cmd_error(curr->cmd, "Is a directory");
        exit(126);
    }
    if (if_cmd_builtin(sh) == 1)
    {
        status = exec_builtin_main(sh);
		free_shell(sh);
        exit(status);
    }
	touch_all_output_files(curr);
	resolve_redir(curr);
	if (curr->heredoc_fd != -1)
	{
		char *cmd_name;
		if (curr->cmd && curr->cmd[0])
			cmd_name = curr->cmd;
		else
			cmd_name = "(null)";
		printf("Applying heredoc_fd for command [%s]: fd=%d\n", cmd_name, curr->heredoc_fd);
	}
	apply_input_red(sh);
    apply_output_red(sh);
    status = execve_bin(sh);
    exit(status);
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
