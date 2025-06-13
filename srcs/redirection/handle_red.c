/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:13:50 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/03 21:39:03 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	apply_input_red(t_cmd *cmd)
{
	int	fd;

	if (!cmd->infile)
		return ;
	fd = open(cmd->infile, O_RDONLY);
	//printf("Opening infile: %s, fd=%d\n", cmd->infile, fd);
	if (fd < 0)
	{
		perror(cmd->infile);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 stdin");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

static void	apply_output_red(t_cmd *cmd)
{
	int	fd;
	int	flags;

	if (!cmd->outfile)
		return ;
	flags = O_WRONLY | O_CREAT;
	if (cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->outfile, flags, 0644);
	if (fd < 0)
	{
		perror(cmd->outfile);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 stdout");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	apply_heredoc_red(t_cmd *cmd, t_env *env)
{
	int	fd;
	int g_exit_status = 0;
	char	*tmpfile;

	if (!cmd->heredoc)
		return ;
	if (ft_strcmp(cmd->infile, "EOF") == 0)
	{
		//fd = heredoc_open(cmd->infile);
		tmpfile = generate_filename();
		//printf("tmp SUCinfile is %s, \n", cmd->infile);
		read_heredoc(cmd->infile, tmpfile, 0, env, g_exit_status);
		//printf("readdoc SUC\n");
		//read_heredoc(cmd->infile, tmpfile, cmd->heredoc_expand, env, g_exit_status);
		free(cmd->infile);
    	cmd->infile = tmpfile; 
		//printf("heredoc process infile is %s, \n", cmd->infile);
	}
	fd = open(cmd->infile, O_RDONLY);
	//printf("infile is %s \n; ",cmd->infile);
	if (fd < 0)
	{
		perror("heredoc:");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 heredoc");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	apply_red(t_cmd *cmd, t_env *env)
{
	if (cmd->heredoc)
		apply_heredoc_red(cmd, env);
	else
		apply_input_red(cmd);
	apply_output_red(cmd);
}

