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

int should_heredoc_expand(const char *delimiter)
{
    int i;
    
    i = 0;
    if (!delimiter)
        return (0);
    while (delimiter[i])
    {
        if (delimiter[i] == '\'' || delimiter[i] == '\"')
            return (0);
        i++;
    }
    return (1);
}

// char *strip_quotes_if_needed(const char *str)
// {
//     char *res;
//     int len;
//     int i;
//     int j;

//     if (!str)
//         return (NULL);
//     len = ft_strlen(str);
//     res = malloc(len + 1);
//     if (!res)
//         return (NULL);
//     i = 0;
//     j = 0;
//     while (str[i])
//     {
//         if (str[i] != '\'' && str[i] != '\"')
//             res[j++] = str[i];
//         i++;
//     }
//     res[j] = '\0';
//     return (res);
// }

char *expand_heredoc_line(char *line, t_env *env, int status)
{
	if (!line)
		return (NULL);
	char *copy = ft_strdup(line);
	if (!copy)
		return (perror("expand_heredoc_line: strdup failed"), NULL);
	return (expand_var_here(copy, env, status));
}

// char	*process_heredoc_content(char *delimiter, t_env *env, int should_expand)
// {
// 	char	*line;
// 	char	*heredoc_content;
// 	char	*expanded_line;
// 	char	*tmp;

// 	heredoc_content = ft_strdup("");
// 	if (!heredoc_content)
// 		return (NULL);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || !ft_strcmp(line, delimiter))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (should_heredoc_expand)
//             expanded_line = expand_string(line, env, 0);
// 		else
// 			expanded_line = line;
// 		tmp = heredoc_content;
// 		heredoc_content = ft_strjoin(heredoc_content, expanded_line);
// 		free(tmp);
// 		if (should_hrerdoc_expand)
// 			free(expanded_line);
// 		heredoc_content = ft_strjoin(heredoc_content, "\n");
// 	}
// 	return (heredoc_content);
// }

char	*process_heredoc_content(char *delimiter, t_env *env, int should_expand, int status)
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
		if (!line || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		if (should_expand)
			expanded_line = expand_heredoc_line(line, env, status);
		else
			// expanded_line = line;else
	        expanded_line = ft_strdup(line);
		line_len = ft_strlen(expanded_line) + 1;
		if (buf_len + line_len + 1 >= buf_size)
		{
            new_size = buf_size * 2;
			new_buf = malloc(buf_size * 2);
			if (!new_buf)
				return (free(buffer), NULL);
			ft_memcpy(new_buf, buffer, buf_len);
			free(buffer);
			buffer = new_buf;
			// buf_size *= 2;
            buf_size = new_size;
		}
		ft_memcpy(buffer + buf_len, expanded_line, line_len - 1);
		buf_len += line_len - 1;
		buffer[buf_len++] = '\n';
		buffer[buf_len] = '\0';
		if (should_expand)
			free(expanded_line);
	}
	return (buffer);
}
