/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:27:39 by jinhuang          #+#    #+#             */
/*   Updated: 2025/05/22 20:42:57 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// static char	*get_user(t_shell *shell)
// {
// 	char	*user_env;

// 	user_env = ft_strjoin(get_env_var_value(shell->env, "USER"), " ");
// 	if (!user_env)
// 		user_env = ft_strdup("guest");
// 	return (user_env);
// }
static char	*get_user(t_shell *shell)
{
	char	*user_env;

	user_env = ft_strjoin(get_env_var_value(shell, "USER"), " ");
	if (!user_env)
		user_env = ft_strdup("guest");
	return (user_env);
}


// char	*build_prompt(t_shell *shell)
// {
// 	char	*tmp;
// 	char	*res;
// 	char	*home;

// 	tmp = get_user(shell);
// 	res = ft_strjoin(tmp, "@minishell");
// 	free(tmp);
// 	home = build_home(shell);
// 	tmp = ft_strjoin(home, res);
// 	free(res);
// 	free(home);
// 	res = ft_strjoin(tmp, "$ ");
// 	free(tmp);
// 	tmp = ft_strjoin(res, DEFAULT);
// 	free(res);
// 	return (tmp);
// }


char	*build_prompt(t_shell *shell)
{
	char	*tmp;
	char	*res;
	char	*home;

	tmp = get_user(shell);
	res = ft_strjoin(tmp, "@minishell");
	if (!res)
		return (free(tmp), NULL);
	free(tmp);
	home = build_home(shell);
	if (!home)
		return (free(tmp), free(res), NULL);
	tmp = ft_strjoin(home, res);
	if (!tmp)
		return (free(res), free(home), NULL);
	free(res);
	free(home);
	res = ft_strjoin(tmp, "$ ");
	if (!res)
		return (free(tmp), free(home), NULL);
	free(tmp);
	tmp = ft_strjoin(res, DEFAULT);
	if (!tmp)
		return (free(res), free(home), NULL);
	free(res);
	return (tmp);
}