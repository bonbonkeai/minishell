#include "minishell.h"

int check_heredoc_expand(const char *delimiter)
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

char *strip_quotes_if_needed(const char *str)
{
    char *res;
    int len;
    int i;
    int j;

    if (!str)
        return (NULL);
    len = ft_strlen(str);
    res = malloc(len + 1);
    if (!res)
        return (NULL);
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] != '\'' && str[i] != '\"')
            res[j++] = str[i];
        i++;
    }
    res[j] = '\0';
    return (res);
}

int should_expand_heredoc(const char *delimiter)
{
    return check_heredoc_expand(delimiter);
}

char *expand_heredoc_line(const char *line, t_env *env)
{
    return expand_string(ft_strdup(line), env, 0);
}

char	*process_heredoc_content(char *delimiter, t_env *env, int should_expand)
{
	char	*line;
	char	*heredoc_content;
	char	*expanded_line;
	char	*tmp;

	heredoc_content = ft_strdup("");
	if (!heredoc_content)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		if (should_expand)
            expanded_line = expand_string(line, env, 0);
		else
			expanded_line = line;
		tmp = heredoc_content;
		heredoc_content = ft_strjoin(heredoc_content, expanded_line);
		free(tmp);
		if (should_expand)
			free(expanded_line);
		heredoc_content = ft_strjoin(heredoc_content, "\n");
	}
	return (heredoc_content);
}

