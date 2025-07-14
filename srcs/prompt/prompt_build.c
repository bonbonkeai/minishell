/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:27:39 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/02 18:37:53 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*get_user(t_shell *shell)
{
	char	*user_env;

	if (!shell || !shell->env)
		return (NULL);
	user_env = ft_strjoin(get_env_var_value(shell, "USER"), "🍭");
	if (!user_env)
		user_env = ft_strdup("jingyi&jinhuang[;(]");
	return (user_env);
}

char	*build_prompt(t_shell *shell)
{
	char	*user;
	char	*res;
	char	*styled;

	if (!shell)
		return (NULL);
	user = get_user(shell);
	if (!user)
		return (NULL);
	res = ft_strjoin(user, "@minishell$🌱 ");
	free(user);
	if (!res)
		return (NULL);
	styled = ft_strjoin(CYAN_BOLD_UNDERLINE, res);
	free(res);
	if (!styled)
		return (NULL);
	res = ft_strjoin(styled, DEFAULT);
	free(styled);
	return (res);
}

static char	*add_prefix(const char *str)
{
	char	*spaced;
	char	*final;

	spaced = ft_strjoin(" ", str);
	if (!spaced)
		return (NULL);
	final = ft_strjoin(spaced, BLUE);
	free(spaced);
	if (!final)
		return (NULL);
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
	home = get_env_var_value(shell, "HOME");
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
	if (!res)
		return (NULL);
	final = add_prefix(res);
	free(res);
	if (!final)
		return (NULL);
	return (final);
}
