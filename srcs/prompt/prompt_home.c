/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:55:47 by jinhuang          #+#    #+#             */
/*   Updated: 2025/05/22 20:26:55 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	*add_prefix(const char *str)
{
	char	*spaced;
	char	*final;

	spaced = ft_strjoin(" ", str);
	final = ft_strjoin(spaced, BLUE);
	free(spaced);
	return (final);
}

static char	*get_home(t_shell *shell)
{
	char	*cwd;
	char	*home;
	char	*res;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup(" ");
	home = get_env_var_value(shell->env, "HOME");
	if (home && home[0] && ft_strnstr(cwd, home, ft_strlen(cwd)))
	{	
		res = ft_strjoin("~", cwd + ft_strlen(home));
		free(cwd);
	}
	else
		res = cwd;
	return (res);
}

char	*build_home(t_shell *shell)
{
	char	*res;
	char	*final;

	res = get_home(shell);
	final = add_prefix(res);
	return (final);
}
