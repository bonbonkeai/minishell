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
