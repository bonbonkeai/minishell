/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_util3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:45:05 by jdu               #+#    #+#             */
/*   Updated: 2025/07/16 14:13:05 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input_redir(t_cmd *cmd, char *op, char *file)
{
	if (!op || !file || !cmd)
		return (-1);
	if (!ft_strcmp(op, "<"))
	{
		if (access(file, F_OK) != 0 || access(file, R_OK) != 0)
		{
			perror(file);
			return (-1);
		}
		cmd->heredoc = 0;
	}
	else if (!ft_strcmp(op, "<<"))
		cmd->heredoc = 1;
	else
		return (0);
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = ft_strdup(file);
	if (!cmd->infile)
		return (-1);
	return (0);
}

int	handle_output_redir(t_cmd *cmd, char *op, char *file)
{
	char	*tmp;

	if (!cmd || !op || !file)
		return (-1);
	tmp = ft_strdup(file);
	if (!tmp)
		return (-1);
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
	else
		return (0);
	return (0);
}

int	input_red(t_shell *sh, t_cmd *cmd, int *storage)
{
	if (cmd->infile)
	{
		if (cmd->heredoc)
		{
			if (apply_heredoc_fd(sh, cmd, storage) < 0)
				return (-1);
		}
		else
		{
			if (apply_input_red(sh, storage) < 0)
				return (-1);
		}
	}
	return (0);
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
