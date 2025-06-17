/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:27:42 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/10 19:52:21 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_heredoc_file(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror("heredoc: open outfile");
	return (fd);
}

/* static int	write_heredoc_line(char *line, int fd, int exp, t_env *env, int status)
{
	char	*expanded;

	if (!exp)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		return (1);
	}
	expanded = expand_string(line, env, status);
	if (!expanded)
		return (0);
	write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
	free(expanded);
	return (1);
} */

int	read_heredoc(char *end_word, char *outfile, int exp, t_env *env, int s)
{
	int	fd;
	char	*line;
	// size_t	len;

	(void)s;
	(void)env;
	(void)exp;
	line = NULL;
	// len = 0;
	fd = open_heredoc_file(outfile);
	if (fd < 0)
		return (-1);
	while (1)
	{
		//printf("HEY IAM IN READHOC");
		line = readline("> ");
		if (!line)
			break;
		if (ft_strcmp(line, end_word) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
        /*if (!write_heredoc_line(line, fd, exp, env, s))
		{
			free(line);
			close(fd);
			return (-1);
		} */
		free(line);
	}
	close(fd);
	return (0);
}

char	*generate_filename(void)
{
	static int	count;
	char	*num_str;
	char	*prefix;
	char	*filename;
	int	i;
	int	j;

	count = 0;
	num_str = ft_itoa(count++);
	prefix = "/tmp/heredoc_tmp_";
	i = 0;
	j = 0;
	filename = malloc(ft_strlen(prefix) + ft_strlen(num_str) + 1);
	if (!filename)
	{
		free(num_str);
		return (NULL);
	}
	while (prefix[i])
	{
		filename[i] = prefix[i];
		i++;
	}
	while (num_str[j])
		filename[i++] = num_str[j++];
	filename[i] = '\0';
	free(num_str);
	return (filename);
}

