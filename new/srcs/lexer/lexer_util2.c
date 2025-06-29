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

int is_empty_command(const char *input)
{
    int i;
    
    i = 0;
    if (!input)
        return (TRUE);
    while (input[i])
    {
        if (!ft_isspace(input[i]))
            return (FALSE);
        i++;
    }
    return (TRUE);
}

int is_specific_case(t_shell *s)
{
	int len;

	if (!s->trimmed_prompt)
		return (TRUE);
	len = ft_strlen(s->trimmed_prompt);
	if ((s->trimmed_prompt[0] == '"' && s->trimmed_prompt[len - 1] == '"') ||
		(s->trimmed_prompt[0] == '\'' && s->trimmed_prompt[len - 1] == '\''))
	{
        s->status = 127;
        ft_putstr_fd("minishell: : command not found\n", 2);
        return (TRUE);
	}
	return (FALSE);
}