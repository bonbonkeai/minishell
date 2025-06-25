/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:35:07 by jdu               #+#    #+#             */
/*   Updated: 2024/12/06 14:41:26 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *p, size_t old_size, size_t new_size)
{
	char	*new_p;

	if (!p)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(p);
		return (NULL);
	}
	new_p = malloc(new_size);
	if (!new_p)
		return (NULL);
	ft_memcpy(new_p, p, old_size);
	free(p);
	return (new_p);
}
