/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:32:17 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/09 14:28:13 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_shell *sh)
{
	char	*pth;
	int		i;
	char	err[2];

	while (sh->cmd->args[1])
	{
		i = 0;
		if (sh->cmd->args[1] && sh->cmd->args[1][i] == '-')
		{
			err[0] = sh->cmd->args[1][0];
			err[1] = sh->cmd->args[1][1];
			return (ft_fprintf(2, ERR_PWD, err), 2);
		}
		else
			break ;
	}
	pth = getcwd(NULL, 0);
	if (!pth)
	{
		perror("pwd:");
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", pth);
	free(pth);
	return (EXIT_SUCCESS);
}
