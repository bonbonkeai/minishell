#include "minishell.h"

int	expand_heredoc_in_cmd_list(t_cmd *cmd_list, t_env *env, int status)
{
	char	*heredoc_content;
	int		fd[2];
    int     should_expand;
    char    *lim;

	while (cmd_list)
	{
        if (cmd_list->heredoc && cmd_list->heredoc_limiter)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				return (1);
			}
            should_expand = !has_quote(cmd_list->heredoc_limiter);
            lim = remove_quotes(cmd_list->heredoc_limiter);
			heredoc_content = process_heredoc_content(lim, env, should_expand, status);
            free(lim);
			if (!heredoc_content)
			{
				close(fd[0]);
				close(fd[1]);
				return (1);
			}
			write(fd[1], heredoc_content, ft_strlen(heredoc_content));
			close(fd[1]);
			free(heredoc_content);
            free(cmd_list->heredoc_limiter);
			cmd_list->heredoc_limiter = NULL;
			cmd_list->heredoc_fd = fd[0];
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}

char *expand_var_here(char *input, t_env *lst_env, int status)
{
    t_expansion exp;

    if (!input)
        return (NULL);
    if (!init_expand(&exp))
        return (free(input), NULL);
    exp.str = input;
    exp.status = status;
    while (input[exp.i] != '\0')
    {
        if (expand_var_here_check(input, &exp, lst_env))
            return (free(input), free(exp.buf), NULL);
        if (exp.len >= exp.size && !handle_buffer(&exp))
            return (free(input), free(exp.buf), NULL);
    }
    exp.buf[exp.len] = '\0';
    return (free(input), exp.buf);
}

int expand_var_here_check(char *input, t_expansion *exp, t_env *lst_env)
{
    // if (input[exp->i] == '\'' && !exp->in_dquote)
    // {
    //     exp->in_squote = !exp->in_squote;
    //     exp->i++;
    // }
    if (input[exp->i] == '\'' && !exp->in_dquote)
    {
        exp->i++;
        while (input[exp->i] && input[exp->i] != '\'')
            exp->buf[exp->len++] = input[exp->i++];
        if (input[exp->i] == '\'')
            exp->i++;
    }
    else if (input[exp->i] == '"' && !exp->in_squote)
    {
        exp->in_dquote = !exp->in_dquote;
        exp->i++;
    }
    else if (input[exp->i] == '$' && valid_exp(input[exp->i + 1]))
    {
        if (!handle_dollar(input, exp, lst_env))
            return (1);
    }
    else
        exp->buf[exp->len++] = input[exp->i++];
    return (0);
}

char *remove_quotes(const char *str)
{
    size_t len;
    
    len = ft_strlen(str);
    if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"') || 
                     (str[0] == '\'' && str[len - 1] == '\'')))
    {
        return ft_substr(str, 1, len - 2);
    }
    return ft_strdup(str);
}
