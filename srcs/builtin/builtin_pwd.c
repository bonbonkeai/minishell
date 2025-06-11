/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:32:17 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/07 18:36:18 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	exec_pwd(int argc __attribute((unused)))
{
	char	*pth;

	pth = getcwd(NULL, 0);
	if (!pth)
	{
		perror("pwd:");
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", pth);
	//free(str);
	return (EXIT_SUCCESS);
}
