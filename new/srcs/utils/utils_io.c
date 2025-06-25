/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 21:10:36 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/07 21:30:31 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	save_std_io(int storage[2])
{
	storage[0] = dup(STDIN_FILENO);
	if (storage[0] == -1)
		return (false);
	storage[1] = dup(STDOUT_FILENO);
	if (storage[1] == -1)
	{
		close(storage[0]);
		return (false);
	}
	return (true);
}

bool	restore_std_io(int storage[2])
{
	bool	res;
	
	res = true;
	if (dup2(storage[0], STDIN_FILENO) == -1)
		res = false;
	if (dup2(storage[1], STDOUT_FILENO) == -1)
		res = false;
	return (res);
}
