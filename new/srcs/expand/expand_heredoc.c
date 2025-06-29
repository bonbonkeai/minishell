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


// int expand_heredoc_in_cmd_list(t_shell *sh)
// {
//     t_cmd *curr;
//     char *lim;
//     char *heredoc_content;
//     char *op;
//     char *target;
//     int fd[2];
//     int should_expand;
//     int i;

//     curr = sh->cmd;
//     while (curr)
//     {
//         i = 0;
//         while (curr->red && curr->red[i] && curr->red[i + 1])
//         {
//             op = curr->red[i];
//             target = curr->red[i + 1];
//             if (!ft_strcmp(op, "<<"))
//             {
//                 if (pipe(fd) == -1)
//                 {
//                     perror("pipe");
//                     return (1);
//                 }
//                 should_expand = !has_quote(target);
//                 lim = merge_quoted_string(target);
//                 if (!lim)
//                     return (1);
//                 heredoc_content = process_heredoc_content(lim, sh, should_expand);
//                 free(lim);
//                 if (!heredoc_content)
//                 {
//                     close(fd[0]);
//                     close(fd[1]);
//                     return (1);
//                 }
//                 write(fd[1], heredoc_content, ft_strlen(heredoc_content));
//                 close(fd[1]);
//                 free(heredoc_content);
//                 if (curr->heredoc_fd != -1)
//                     close(curr->heredoc_fd);
//                 curr->heredoc_fd = fd[0];
//             }
//             i += 2;
//         }
//         curr = curr->next;
//     }
//     return (0);
// }

static int handle_heredoc(t_cmd *cmd, t_shell *sh, char *target)
{
    int fd[2];
    char *lim;
    char *heredoc_content;
    int should_expand;

    if (pipe(fd) == -1)
        return (perror("pipe"), 1);
    should_expand = !has_quote(target);
    lim = merge_quoted_string(target);
    if (!lim)
        return (close(fd[0]), close(fd[1]), 1);
    heredoc_content = process_heredoc_content(lim, sh, should_expand);
    free(lim);
    if (!heredoc_content)
        return (close(fd[0]), close(fd[1]), 1);
    write(fd[1], heredoc_content, ft_strlen(heredoc_content));
    close(fd[1]);
    free(heredoc_content);
    if (cmd->heredoc_fd != -1)
        close(cmd->heredoc_fd);
    cmd->heredoc_fd = fd[0];
    return (0);
}

static int process_cmd_heredocs(t_cmd *cmd, t_shell *sh)
{
    int i;

    i = 0;
    while (cmd->red && cmd->red[i] && cmd->red[i + 1])
    {
        if (!ft_strcmp(cmd->red[i], "<<"))
        {
            if (handle_heredoc(cmd, sh, cmd->red[i + 1]))
                return (1);
        }
        i += 2;
    }
    return (0);
}

int expand_heredoc_in_cmd_list(t_shell *sh)
{
    t_cmd *curr;

    curr = sh->cmd;
    while (curr)
    {
        if (process_cmd_heredocs(curr, sh))
            return (1);
        curr = curr->next;
    }
    return (0);
}


char *expand_var_here(char *input, t_shell *sh)
{
    t_expansion exp;
    char *expbuf;

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
    expbuf = ft_strdup(exp.buf);
    if (!expbuf)
        return (free(input), NULL);
    free_expansion(&exp);
    return (free(input), expbuf);
}

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

