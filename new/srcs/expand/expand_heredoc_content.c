/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_content.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:40:18 by jdu               #+#    #+#             */
/*   Updated: 2025/07/02 17:42:02 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc_line(char *line, t_shell *sh)
{
	char	*copy;

	if (!line)
		return (NULL);
	copy = ft_strdup(line);
	if (!copy)
		return (perror("expand_heredoc_line: strdup failed"), NULL);
	return (expand_var_here(copy, sh));
}

static char	*init_buffer(size_t size)
{
	char	*buf;

	buf = malloc(size);
	if (buf)
		buf[0] = '\0';
	return (buf);
}

static int	append_to_buffer(char **buffer, size_t *buf_len, char *line)
{
	size_t	buf_size;
	size_t	line_len;
	char	*new_buf;

	buf_size = ft_strlen(*buffer) + 1024;
	line_len = ft_strlen(line) + 1;
	if (*buf_len + line_len + 1 >= buf_size)
	{
		new_buf = malloc(buf_size * 2);
		if (!new_buf)
			return (free(*buffer), 0);
		ft_memcpy(new_buf, *buffer, *buf_len);
		free(*buffer);
		*buffer = new_buf;
	}
	ft_memcpy(*buffer + *buf_len, line, line_len - 1);
	*buf_len += line_len - 1;
	(*buffer)[(*buf_len)++] = '\n';
	(*buffer)[*buf_len] = '\0';
	return (1);
}

static bool	process_heredoc_line(char **buffer, size_t *buf_len, \
		char *line, t_shell *sh)
{
	char	*expanded;

	if (sh->should_expand)
		expanded = expand_heredoc_line(line, sh);
	else
		expanded = ft_strdup(line);
	free(line);
	if (!expanded)
		return (free(*buffer), false);
	if (!append_to_buffer(buffer, buf_len, expanded))
	{
		free(expanded);
		return (false);
	}
	free(expanded);
	return (true);
}

char	*process_heredoc_content(char *delimiter, t_shell *sh)
{
	char	*buffer;
	size_t	buf_len;
	char	*line;

	buffer = init_buffer(1024);
	if (!buffer)
		return (NULL);
	buf_len = 0;
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT || !line || !ft_strcmp(line, delimiter))
		{
			free(line);
			if (g_signal == SIGINT)
				return (free(buffer), NULL);
			break ;
		}
		if (!process_heredoc_line(&buffer, &buf_len, line, sh))
			return (NULL);
	}
	return (buffer);
}
