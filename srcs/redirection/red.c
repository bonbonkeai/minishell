/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:44:57 by jdu               #+#    #+#             */
/*   Updated: 2025/07/01 21:26:16 by jdu              ###   ########.fr       */
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

void	resolve_redir(t_cmd *cmd)
{
	int		i;
	char	*op;
	char	*file;

	i = 0;
	if (!cmd || !cmd->red)
		return ;
	while (cmd->red[i] && cmd->red[i + 1])
	{
		op = cmd->red[i];
		file = cmd->red[i + 1];
		if (!ft_strcmp(op, "<"))
			handle_input_redir(cmd, op, file);
		else if (!ft_strcmp(op, ">") || !ft_strcmp(op, ">>"))
			handle_output_redir(cmd, op, file);
		i += 2;
	}
}


// int	resolve_redir(t_cmd *cmd)
// {
// 	int		i;
// 	char	*op;
// 	char	*file;
// 	int		fd;
// 	int		flags;

// 	if (!cmd || !cmd->red)
// 		return (-1);
// 	i = 0;
// 	while (cmd->red[i] && cmd->red[i + 1])
// 	{
// 		op = cmd->red[i];
// 		file = cmd->red[i + 1];
// 		if (!ft_strcmp(op, "<"))
// 		{
// 			fd = open(file, O_RDONLY);
// 			if (fd < 0)
// 			{
// 				perror(file);
// 				return (-1);
// 			}
// 			if (dup2(fd, STDIN_FILENO) == -1)
// 			{
// 				perror("dup2 stdin");
// 				close(fd);
// 				return (-1);
// 			}
// 			close(fd);
// 		}
// 		else if (!ft_strcmp(op, ">") || !ft_strcmp(op, ">>"))
// 		{
// 			flags = O_WRONLY | O_CREAT;
// 			if (!ft_strcmp(op, ">>"))
// 				flags |= O_APPEND;
// 			else
// 				flags |= O_TRUNC;
// 			fd = open(file, flags, 0644);
// 			if (fd < 0)
// 			{
// 				perror(file);
// 				return (-1);
// 			}
// 			if (dup2(fd, STDOUT_FILENO) == -1)
// 			{
// 				perror("dup2 stdout");
// 				close(fd);
// 				return (-1);
// 			}
// 			close(fd);
// 		}
// 		i += 2;
// 	}
// 	return (0);
// }


// void	touch_all_output_files(t_cmd *cmd)
// {
// 	int	fd;
// 	int	i;

// 	if (!cmd || !cmd->red)
// 		return ;
// 	i = 0;
// 	while (cmd->red[i])
// 	{
// 		if (ft_strcmp(cmd->red[i], ">") == 0 \
// 		|| ft_strcmp(cmd->red[i], ">>") == 0)
// 		{
// 			if (cmd->red[i + 1])
// 			{
// 				fd = open(cmd->red[i + 1], O_WRONLY | O_CREAT, 0644);
// 				if (fd < 0)
//                     perror(cmd->red[i + 1]);
// 				else
// 					close(fd);
// 				i++;
// 			}
// 		}
// 		i++;
// 	}
// }

bool	touch_all_output_files(t_cmd *cmd)
{
	int	fd;
	int	i;

	if (!cmd || !cmd->red)
		return (true);
	i = 0;
	while (cmd->red[i])
	{
		if (ft_strcmp(cmd->red[i], ">") == 0 \
		|| ft_strcmp(cmd->red[i], ">>") == 0)
		{
			if (cmd->red[i + 1])
			{
				fd = open(cmd->red[i + 1], O_WRONLY | O_CREAT, 0644);
				if (fd < 0)
				{
					perror(cmd->red[i + 1]);
					return (false);
				}
				else
					close(fd);
				i++;
			}
		}
		i++;
	}
	return (true);
}

int	count_redirs(char **red)
{
	int	len;

	len = 0;
	while (red && red[len])
		len++;
	return (len);
}
