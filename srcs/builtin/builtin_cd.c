/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:56:49 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/12 20:10:54 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_error(char *msg, char *arg)
{
	write(2, "cd: ", 4);
	if (arg)
		write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

static char	*resolve_cd_target(t_env *env, char **argv)
{
	int	len;

	len = 0;
	while (argv[len])
		len++;
	if (len < 2 || !argv[1])
		return (get_env_var_value(env, "HOME"));
	else if (ft_strcmp(argv[1], "-") == 0)
		return (get_env_var_value(env, "OLDPWD"));
	else
		return (argv[1]);
}

static void	update_pwd_vars(char *oldpwd, t_shell *shell)
{
	char	cwd[PATH_MAX];

	env_set_var("OLDPWD", oldpwd, &(shell->env), 0);
	if (getcwd(cwd, sizeof(cwd)))
		env_set_var("PWD", cwd, &(shell->env), 0);
}

int	builtin_cd(t_shell *shell, char **argv)
{
	char	*target;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		write(2, "cd: getcwd failed\n", 18);
		return (1);
	}
	target = resolve_cd_target(shell->env, argv);
	if (!target)
	{
		cd_error("HOME not set", "cd");
		free(oldpwd);
		return (1);
	}
	if (chdir(target) != 0)
	{
		cd_error("No such file or directory", target);
		free(oldpwd);
		return (1);
	}
	update_pwd_vars(oldpwd, shell);
	free(oldpwd);
	return (0);
}
