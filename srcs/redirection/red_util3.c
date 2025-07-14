/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_util3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:45:05 by jdu               #+#    #+#             */
/*   Updated: 2025/07/11 20:42:24 by jinhuang         ###   ########.fr       */
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

void	process_input_redir(t_shell *sh, char *op, char *file)
{
	t_cmd	*cmd;

	cmd = sh->curr_cmd;
	if (!ft_strcmp(op, "<"))
		handle_input_redir(cmd, op, file);
}

int	apply_heredoc_fd(t_shell *sh, t_cmd *cmd, int *storage)
{
	if (!cmd || cmd->heredoc_fd == -1)
		return (0);
	if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 heredoc_fd");
		safe_close(sh, storage);
		return (-1);
	}
	return (0);
}

int	count_redirs(char **red)
{
	int	len;

	len = 0;
	while (red && red[len])
		len++;
	return (len);
}
