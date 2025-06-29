/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:46:55 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:46:56 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_heredoc_line(char *line, t_shell *sh)
{
	char *copy;

	if (!line)
		return (NULL);
	copy = ft_strdup(line);
	if (!copy)
		return (perror("expand_heredoc_line: strdup failed"), NULL);
	return (expand_var_here(copy, sh));
}


// char	*process_heredoc_content(char *delimiter, t_shell *sh, int should_expand)
// {
// 	char	*line;
// 	char	*expanded_line;
// 	char	*buffer;
// 	size_t	buf_size = 1024;
// 	size_t	buf_len = 0;
// 	size_t	line_len;
//     size_t  new_size;
//     char *new_buf;

// 	buffer = malloc(buf_size);
// 	if (!buffer)
// 		return (NULL);
// 	buffer[0] = '\0';
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || !ft_strcmp(line, delimiter))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (should_expand)
// 			expanded_line = expand_heredoc_line(line, sh);
// 		else
// 	        expanded_line = ft_strdup(line);
// 		free(line);
// 		if (!expanded_line)
// 			return (free(buffer), NULL);
// 		line_len = ft_strlen(expanded_line) + 1;
// 		if (buf_len + line_len + 1 >= buf_size)
// 		// if (buf_len + line_len + 2 >= buf_size)
// 		{
//             new_size = buf_size * 2;
// 			new_buf = malloc(buf_size * 2);
// 			if (!new_buf)
// 				return (free(expanded_line), free(buffer), NULL);
// 			ft_memcpy(new_buf, buffer, buf_len);
// 			free(buffer);
// 			buffer = new_buf;
//             buf_size = new_size;
// 		}
// 		ft_memcpy(buffer + buf_len, expanded_line, line_len - 1);
// 		// ft_memcpy(buffer + buf_len, expanded_line, line_len);
// 		buf_len += line_len - 1;
// 		// buf_len += line_len;
// 		buffer[buf_len++] = '\n';
// 		buffer[buf_len] = '\0';
// 		free(expanded_line);
// 	}
// 	return (buffer);
// }

static char *init_buffer(size_t size)
{
    char *buf;
	
	buf = malloc(size);
    if (buf)
        buf[0] = '\0';
    return (buf);
}

static int append_to_buffer(char **buffer, size_t *buf_len, char *line)
{
    size_t buf_size;
    size_t line_len;

	buf_size = ft_strlen(*buffer) + 1024;
	line_len = ft_strlen(line) + 1;  
    if (*buf_len + line_len + 1 >= buf_size)
    {
        char *new_buf = malloc(buf_size * 2);
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

static bool process_heredoc_line(char **buffer, size_t *buf_len, char *line, t_shell *sh, int should_expand)
{
    char *expanded;

    if (should_expand)
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

char *process_heredoc_content(char *delimiter, t_shell *sh, int should_expand)
{
    char *buffer;
    size_t buf_len;
    char *line;

    buffer = init_buffer(1024);
    if (!buffer)
        return (NULL);
    buf_len = 0;
    while (1)
    {
        line = readline("> ");
        if (!line || !ft_strcmp(line, delimiter))
        {
            free(line);
            break ;
        }
        if (!process_heredoc_line(&buffer, &buf_len, line, sh, should_expand))
            return (NULL);
    }
    return (buffer);
}
