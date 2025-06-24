/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:47:10 by jdu               #+#    #+#             */
/*   Updated: 2024/12/06 14:01:43 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_newline(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (&buffer[i]);
		i++;
	}
	return (NULL);
}

static char	*obtenir_un_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer || !buffer[0])
		return (free(buffer), NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = (char *)malloc(i + 2);
	else
		line = (char *)malloc(i + 1);
	if (!line)
		return (free(buffer), NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	return (line[i] = '\0', line);
}

static char	*recomposer_line(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), buffer = NULL, NULL);
	new_buffer = (char *)malloc(ft_strlen(buffer) - i + 1);
	if (!new_buffer)
		return (free(buffer), buffer = NULL, NULL);
	i++;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*fill_buffer(int fd, char *buffer)
{
	int		len_read;
	char	*temp;
	char	*old_buffer;

	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (free(buffer), NULL);
	while (!find_newline(buffer))
	{
		len_read = read(fd, temp, BUFFER_SIZE);
		if (len_read < 0)
			return (free(buffer), free(temp), NULL);
		if (len_read == 0)
			break ;
		temp[len_read] = '\0';
		old_buffer = buffer;
		buffer = ft_strjoin(buffer, temp);
		free(old_buffer);
		if (!buffer)
			return (free(temp), NULL);
	}
	free(temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (free(buffer), buffer = NULL, NULL);
	buffer = fill_buffer(fd, buffer);
	if (!buffer || !buffer[0])
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = obtenir_un_line(buffer);
	if (!line)
		return (buffer = NULL, NULL);
	buffer = recomposer_line(buffer);
	return (line);
}
