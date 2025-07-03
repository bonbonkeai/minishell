/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:39:30 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/02 16:40:53 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bubble_sort_env(t_env **arr, int size)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(arr[j]->key, arr[j + 1]->key) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	ft_perror_export(char *arg)
{
	write(2, "minishell: export: `", 20);
	ft_putstr_fd(arg, 2);
	write(2, "': not a valid identifier\n", 26);
}
