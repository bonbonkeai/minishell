/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:33:59 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/05 20:16:54 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_cmd_builtin(t_cmd *cmd)
{
	int	re;

	re = 0;
	if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		re = 1;
	else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		re = 1;
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		re = 1;
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		re = 1;
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		re = 1;
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		re = 1;
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		re = 1;
	return (re);
}

int	if_cmd_start(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "(") == 0)
		return (1);
	else
		return (0);
}

int	if_cmd_simple(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "(") != 0)
	{
		if (cmd->next == NULL)
			return (1);
		else 
			return (0);
	}
	return (2);
}

void	exec_simple_exit(t_cmd *cmd)
{
	if (cmd)
		free_cmd_list(cmd);
}


// char	*join_path_cmd(char *path, char *cmd) 
// {
//     int i = 0, j = 0;
//     // 计算 path 长度
//     while (path[i] != '\0') i++;
//     // 计算 cmd 长度
//     while (cmd[j] != '\0') j++;

//     // 额外 +1 是加中间的 '/'，再 +1 是结尾 '\0'
//     char *result = malloc(i + 1 + j + 1);
//     if (!result)
//         return NULL;

//     int k = 0;
//     int p = 0;
//     // 复制 path
//     while (p < i) {
//         result[k++] = path[p++];
//     }

//     // 如果 path 末尾不是 '/'，就加一个 '/'
//     if (i > 0 && path[i - 1] != '/') {
//         result[k++] = '/';
//     }

//     // 复制 cmd
//     p = 0;
//     while (p < j) {
//         result[k++] = cmd[p++];
//     }

//     result[k] = '\0';
//     return result;
// }

int	exec_wait_pid(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			ft_putendl_fd("Quit: 3", STDERR_FILENO);
		else if (WTERMSIG(status) == 2)
			ft_putstr_fd("\n", STDERR_FILENO);
		status = 128 + WTERMSIG(status);
	}
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}
