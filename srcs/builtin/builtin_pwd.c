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

	if (sh->cmd->args[1] && sh->cmd->args[1][0] == '-')
		return (ft_printf(ERR_PWD), 2);
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
