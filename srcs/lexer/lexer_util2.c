/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:16:44 by jdu               #+#    #+#             */
/*   Updated: 2025/07/01 20:51:30 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty_command(const char *input)
{
	int	i;

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

/*int	is_specific_case(t_shell *s)
{
	int	len;

	if (!s->trimmed_prompt)
		return (TRUE);
	len = ft_strlen(s->trimmed_prompt);
	if ((s->trimmed_prompt[0] == '"' && s->trimmed_prompt[len - 1] == '"') || \
	(s->trimmed_prompt[0] == '\'' && s->trimmed_prompt[len - 1] == '\''))
	{
		s->status = 127;
		print_cmd_error(s->trimmed_prompt, ERR_COMMAND);
		return (TRUE);
	}
	return (FALSE);
}*/
