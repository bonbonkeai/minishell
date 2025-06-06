#include "minishell.h"

int	expand_heredocs_in_cmd_list(t_cmd *cmd_list, t_env *env)
{
	char	*heredoc_content;
	int		fd[2];
    int     should_expand;

	while (cmd_list)
	{
		if (cmd_list->heredoc && cmd_list->infile)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				return (1);
			}
			should_expand = !has_quote(cmd_list->infile);
			heredoc_content = process_heredoc_content(cmd_list->infile, env, should_expand);
			if (!heredoc_content)
			{
				close(fd[0]);
				close(fd[1]);
				return (1);
			}
			write(fd[1], heredoc_content, ft_strlen(heredoc_content));
			close(fd[1]);
			free(heredoc_content);
			free(cmd_list->infile);
			// cmd_list->infile = ft_strdup("/tmp/.heredoc");
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
    while (input[exp.i] != '\0')
    {
        if (expand_var_here_check(input, &exp, lst_env, status))
            return (free(input), free(exp.buf), NULL);
        if (exp.len >= exp.size && !handle_buffer(&exp))
            return (free(input), NULL);
    }
    exp.buf[exp.len] = '\0';
    return (free(input), exp.buf);
}

int expand_var_here_check(char *input, t_expansion *exp, t_env *lst_env, int status)
{
    if (input[exp->i] == '\'' && !exp->in_dquote)
    {
        exp->in_squote = !exp->in_squote;
        exp->buf[exp->len++] = input[exp->i++];
    }
    else if (input[exp->i] == '"' && !exp->in_squote)
    {
        exp->in_dquote = !exp->in_dquote;
        exp->buf[exp->len++] = input[exp->i++];
    }
    else if (input[exp->i] == '$' && valid_exp(input[exp->i + 1]))
    {
        if (!handle_dollar(input, exp, lst_env, status))
            return (1);
    }
    else
        exp->buf[exp->len++] = input[exp->i++];
    return (0);
}

