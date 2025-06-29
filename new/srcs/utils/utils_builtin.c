/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:39:30 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/19 15:39:49 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	bubble_sort_env(t_env **arr, int size)
{
	int	i, j;
	t_env	*temp;

	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (ft_strcmp(arr[j]->key, arr[j + 1]->key) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

/* void	ft_perror_export(char *fmt, char *arg)
{
	write(2, "bash: export: `", 15);
	while (*fmt)
	{
		if (*fmt == '%' && *(fmt + 1) == 's')
		{
			ft_putstr_fd(arg, 2);
			fmt += 2;
		}
		else
		{
			write(2, fmt, 1);
			fmt++;
		}
	}
	write(2, "\n", 1);
} */

void	ft_perror_export(char *arg)
{
	write(2, "bash: export: `", 15);
	ft_putstr_fd(arg, 2);
	write(2, "': not a valid identifier\n", 26);
}