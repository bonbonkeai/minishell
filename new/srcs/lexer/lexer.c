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

int check_syntax(const char *input)
{
    int in_squote;
    int in_dquote;
    int i;

    in_squote = 0;
    in_dquote = 0;
    i = 0;
    while (input[i])
    {
        toggle_quote(input[i], &in_squote, &in_dquote);
        if (!in_squote && !in_dquote && is_invalid_operator(input, i))
            return (TRUE);
        i++;
    }
    return (check_quotes_closed(in_squote, in_dquote));
}

void toggle_quote(char ch, int *in_squote, int *in_dquote)
{
    if (ch == '\'' && !(*in_dquote))
        *in_squote = !(*in_squote);
    else if (ch == '"' && !(*in_squote))
        *in_dquote = !(*in_dquote);
}


int is_pipe_error(const char *s)
{
	int len;
	
	if (!s)
		return (FALSE);
	len = ft_strlen(s) - 1;
	if (s[0] == '|')
		return (syntax_error('|'), TRUE);
	if (s[len] == '|' || s[len] == '<' || s[len] == '>')
		return (syntax_error_newline(), TRUE);
	return (FALSE);
}

void	syntax_error_newline(void)
{
	write(2, "minishell: syntax error near unexpected token `newline'\n", 57);
}

int lexer(t_shell *shell)
{
    // if (is_empty_command(shell->trimmed_prompt))
    //     return (FALSE);
    if (check_syntax(shell->trimmed_prompt))
    {
        shell->status = 2;
        return (FALSE);
    }
    if (is_pipe_error(shell->trimmed_prompt))
    {
        shell->status = 2;
        return (FALSE);
    }
    if (is_specific_case(shell))
        return (FALSE);
    return (TRUE);
}


