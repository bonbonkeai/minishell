/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_rest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:41:47 by jdu               #+#    #+#             */
/*   Updated: 2025/07/11 20:49:35 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

bool	is_heredoc(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->heredoc_limiter)
		{
			cmd->heredoc = 1;
			return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}

int	assign_cmd_names(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->args && cmd->args[0])
		{
			if (cmd->cmd)
			{
				free(cmd->cmd);
				cmd->cmd = NULL;
			}
			cmd->cmd = ft_strdup(cmd->args[0]);
			if (!cmd->cmd)
				return (0);
		}
		cmd = cmd->next;
	}
	return (1);
}

static void	trim_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

bool	read_heredoc_loop(char **buffer, size_t *buf_len, \
		char *delimiter, t_shell *sh)
{
	char	*line;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = readline("> ");
		else
			line = get_next_line(fileno(stdin));
		if (line && !isatty(STDIN_FILENO))
			trim_newline(line);
		if (!line)
			return (ft_fprintf(2, ERR_S, delimiter), free(*buffer), NULL);
		if (g_signal == SIGINT || !line || !ft_strcmp(line, delimiter))
		{
			free(line);
			if (g_signal == SIGINT)
				return (free(*buffer), NULL);
			break ;
		}
		if (!process_heredoc_line(buffer, buf_len, line, sh))
			return (false);
	}
	return (true);
}
