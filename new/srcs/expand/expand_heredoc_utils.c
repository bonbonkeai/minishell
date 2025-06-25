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

int is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

char	*merge_quoted_string(const char *limiter)
{
	int		i;
	int		j;
	char	*merged;

    i = 0;
    j = 0;
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

int	expand_heredoc_in_cmd_list(t_shell *sh)
{
	char	*heredoc_content;
	int		fd[2];
    int     should_expand;
    char    *lim;
    t_cmd   *curr;

    curr = sh->cmd;
	while (curr)
	{
        //
        sh->curr_cmd = curr;
        //
        if (curr->heredoc && curr->heredoc_limiter)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				return (1);
			}
            should_expand = !has_quote(curr->heredoc_limiter);
            lim = merge_quoted_string(curr->heredoc_limiter);
            if (!lim)
                return (1);
			heredoc_content = process_heredoc_content(lim, sh, should_expand);
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
            free(curr->heredoc_limiter);
			curr->heredoc_limiter = NULL;
			curr->heredoc_fd = fd[0];
            //
            ft_fprintf(2, "[DEBUG] heredoc_fd for cmd '%s' set to %d\n", curr->cmd ? curr->cmd : "(null)", curr->heredoc_fd);
            //
		}
		curr = curr->next;
	}
    //
    sh->curr_cmd = NULL;
    //
	return (0);
}


char *expand_var_here(char *input, t_shell *sh)
{
    t_expansion exp;

    if (!input || !sh)
        return (NULL);
    if (!init_expand(&exp, input, sh->status))
        return (free(input), NULL);
    while (input[exp.i] != '\0')
    {
        if (expand_var_here_check(input, &exp, sh))
            return (free(input), free(exp.buf), NULL);
        if (exp.len >= exp.size && !handle_buffer(&exp))
            return (free(input), free(exp.buf), NULL);
    }
    exp.buf[exp.len] = '\0';
    return (free(input), exp.buf);
}

// int expand_var_here_check(char *input, t_expansion *exp, t_env *lst_env)
// {
//     if (input[exp->i] == '\'' && !exp->in_dquote)
//     {
//         exp->i++;
//         while (input[exp->i] && input[exp->i] != '\'')
//             exp->buf[exp->len++] = input[exp->i++];
//         if (input[exp->i] == '\'')
//             exp->i++;
//     }
//     else if (input[exp->i] == '"' && !exp->in_squote)
//     {
//         exp->in_dquote = !exp->in_dquote;
//         exp->i++;
//     }
//     else if (input[exp->i] == '$' && valid_exp(input[exp->i + 1]))
//     {
//         if (!handle_dollar(input, exp, lst_env))
//             return (1);
//     }
//     else
//         exp->buf[exp->len++] = input[exp->i++];
//     return (0);
// }

int expand_var_here_check(char *input, t_expansion *exp, t_shell *sh)
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
        if (!handle_dollar(input, exp, sh->env))
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
