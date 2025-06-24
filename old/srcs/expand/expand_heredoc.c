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

int has_quote(const char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (1);
		str++;
	}
	return (0);
}

// int should_heredoc_expand(const char *delimiter)
// {
//     int i;
    
//     i = 0;
//     if (!delimiter)
//         return (0);
//     while (delimiter[i])
//     {
//         if (delimiter[i] == '\'' || delimiter[i] == '\"')
//             return (0);
//         i++;
//     }
//     return (1);
// }


char *expand_heredoc_line(char *line, t_shell *sh)
{
	if (!line)
		return (NULL);
	char *copy = ft_strdup(line);
	if (!copy)
		return (perror("expand_heredoc_line: strdup failed"), NULL);
	return (expand_var_here(copy, sh));
}


// char	*process_heredoc_content(char *delimiter, t_env *env, int should_expand, int status)
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
// 			expanded_line = expand_heredoc_line(line, env, status);
// 		else
// 			// expanded_line = line;else
// 	        expanded_line = ft_strdup(line);
// 		line_len = ft_strlen(expanded_line) + 1;
// 		if (buf_len + line_len + 1 >= buf_size)
// 		{
//             new_size = buf_size * 2;
// 			new_buf = malloc(buf_size * 2);
// 			if (!new_buf)
// 				return (free(buffer), NULL);
// 			ft_memcpy(new_buf, buffer, buf_len);
// 			free(buffer);
// 			buffer = new_buf;
// 			// buf_size *= 2;
//             buf_size = new_size;
// 		}
// 		ft_memcpy(buffer + buf_len, expanded_line, line_len - 1);
// 		buf_len += line_len - 1;
// 		buffer[buf_len++] = '\n';
// 		buffer[buf_len] = '\0';
// 		if (should_expand)
// 			free(expanded_line);
// 	}
// 	return (buffer);
// }

char	*process_heredoc_content(char *delimiter, t_shell *sh, int should_expand)
{
	char	*line;
	char	*expanded_line;
	char	*buffer;
	size_t	buf_size = 1024;
	size_t	buf_len = 0;
	size_t	line_len;
    size_t  new_size;
    char *new_buf;

	buffer = malloc(buf_size);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	while (1)
	{
		line = readline("> ");
		// if (!line)
		// 	break ;
		if (!line || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		if (should_expand)
			expanded_line = expand_heredoc_line(line, sh);
		else
	        expanded_line = ft_strdup(line);
		free(line);
		if (!expanded_line)
			return (free(buffer), NULL);
		line_len = ft_strlen(expanded_line) + 1;
		if (buf_len + line_len + 1 >= buf_size)
		// if (buf_len + line_len + 2 >= buf_size)
		{
            new_size = buf_size * 2;
			new_buf = malloc(buf_size * 2);
			if (!new_buf)
				return (free(expanded_line), free(buffer), NULL);
			ft_memcpy(new_buf, buffer, buf_len);
			free(buffer);
			buffer = new_buf;
            buf_size = new_size;
		}
		ft_memcpy(buffer + buf_len, expanded_line, line_len - 1);
		// ft_memcpy(buffer + buf_len, expanded_line, line_len);
		buf_len += line_len - 1;
		// buf_len += line_len;
		buffer[buf_len++] = '\n';
		buffer[buf_len] = '\0';
		free(expanded_line);
	}
	return (buffer);
}
