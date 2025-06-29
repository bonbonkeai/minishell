/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:43:58 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:44:02 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//lexer_error
int check_heredoc_redir_conflict(const char *input, int i)
{
    int j;

    if (input[i] == '<' && input[i + 1] == '<')
    {
        j = i + 2;
        while (input[j] && ft_isspace(input[j]))
            j++;
        if (input[j] == '>' && input[j + 1] == '>')
            return (syntax_error_pipex(">>"), TRUE);
    }
    return (FALSE);
}

int check_long_redir_sequence(const char *input, int i)
{
    int count = 0;

    if (input[i] == '<')
    {
        while (input[i + count] == '<')
            count++;
        if (count > 3)
        {
            if (count > 5)
                return (syntax_error_pipex("<<<"), TRUE);
            else
                return (syntax_error_pipex("<<"), TRUE);
        }
    }
    return (FALSE);
}

int check_pipe_conflict(const char *input, int i)
{
    if ((input[i] == '>' || input[i] == '<') && input[i + 1] == input[i] && input[i + 1] == '|')
        return (syntax_error_pipex("|"), TRUE);
    if ((input[i] == '>' || input[i] == '<') && input[i + 1] == '|')
        return (syntax_error_pipex("|"), TRUE);
    return (FALSE);
}

int check_redir_newline_end(const char *input, int i)
{
    if ((input[i] == '>' || input[i] == '<') && input[i + 1] == '\0')
        return (syntax_error_newline(), TRUE);
    return (FALSE);
}

int check_triple_redir(const char *input, int i)
{
    //cat >>> ; cat <<< ; cat << ; cat >>
    if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>' && input[i + 3] != '>')
        return (syntax_error('>'), TRUE);
    else if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<' && input[i + 3] != '<')
        return (syntax_error_newline(), TRUE);
    if ((input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<' && input[i + 3] != '<') ||
    (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>' && input[i + 3] != '>'))
        return (syntax_error_newline(), TRUE);
    if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<' && input[i + 3] != '<')
        return (syntax_error_newline(), TRUE);
    return (FALSE);
}
