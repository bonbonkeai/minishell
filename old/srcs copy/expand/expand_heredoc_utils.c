/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:47:07 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:47:08 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*merge_quoted_string(const char *limiter)
{
	int		i = 0;
	int		j = 0;
	char	*merged;

	if (!limiter)
		return (NULL);
	merged = malloc(sizeof(char) * (ft_strlen(limiter) + 1));
	if (!merged)
		return (NULL);
	while (limiter[i])
	{
		if (!is_quote(limiter[i]))
			merged[j++] = limiter[i];
		i++;
	}
	merged[j] = '\0';
	return (merged);
}

int is_fully_quoted(const char *s)
{
    int len;

    if (!s)
        return 0;
    len = ft_strlen(s);
    if (len < 2)
        return 0;
    return ((s[0] == '\'' && s[len - 1] == '\'') ||
            (s[0] == '"' && s[len - 1] == '"'));
}


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
            // should_expand = !is_fully_quoted(cmd_list->heredoc_limiter);
                        // lim = merge_quoted_tokens(cmd_list->heredoc_limiter);
            should_expand = !has_quote(cmd_list->heredoc_limiter);
            lim = merge_quoted_string(cmd_list->heredoc_limiter);
            // should_expand = (cmd_list->quote_flag != 1);
			// lim = merge_quoted_tokens(cmd_list->heredoc_limiter);
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
