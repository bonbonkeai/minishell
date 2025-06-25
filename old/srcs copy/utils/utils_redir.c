/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:21:45 by jinhuang          #+#    #+#             */
/*   Updated: 2025/05/28 20:24:14 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_standard_fd(int fd)
{
	if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO)
		return (1);
	return (0);
}

int	check_cmd_standard(t_cmd *cmd)
{
	if (check_standard_fd(cmd->fd_in) && check_standard_fd(cmd->fd_out) && \
		cmd->infile == NULL && cmd ->outfile == NULL)
		return (1);
	return (0);
}

