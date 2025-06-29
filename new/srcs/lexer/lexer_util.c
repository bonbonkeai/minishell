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

int is_too_many_char(const char *input, int i, char c)
{
	int count;
    
    count = 0;
	while (input[i] == c)
	{
		count++;
		i++;
	}
    if (count > 3)
    {
        return (1);
    }
	return (0);
}

char next_non_space(const char *str, int i)
{
    i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (str[i]);
}

void syntax_error(char unexpected)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
    write(2, &unexpected, 1);
    write(2, "'\n", 2);
}

void syntax_error_pipex(char *unexpected)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
    write(2, unexpected, ft_strlen(unexpected));
    write(2, "'\n", 2);
}

int check_quotes_closed(int in_squote, int in_dquote)
{
    if (in_squote)
    {
        ft_putstr_fd("minishell: unexpected EOF while looking for matching '\n", 2);
        return (TRUE);
    }
    if (in_dquote)
    {
        ft_putstr_fd("minishell: unexpected EOF while looking for matching \"\n", 2);
        return (TRUE);
    }
    return (FALSE);
}