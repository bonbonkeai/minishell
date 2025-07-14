/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:56:49 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/11 19:21:37 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_error(char *msg, char *arg)
{
	write(2, "cd: ", 4);
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

static void	update_pwd_vars(char *oldpwd, t_shell *shell)
{
	char	cwd[PATH_MAX];

	env_set_value(shell, "OLDPWD", oldpwd, 0);
	if (getcwd(cwd, sizeof(cwd)))
		env_set_value(shell, "PWD", cwd, 0);
}

static char	*resolve_cd_special_cases(t_shell *sh, char *arg)
{
	char	*home;
	char	*oldpwd;

	if (!arg)
	{
		home = get_env_var_value(sh, "HOME");
		if (home)
			return (ft_strdup(home));
		return (NULL);
	}
	if (ft_strcmp(arg, "~") == 0)
	{
		home = get_env_var_value(sh, "HOME");
		if (home)
			return (ft_strdup(home));
		return (ft_strdup(sh->default_home));
	}
	else if (ft_strcmp(arg, "-") == 0)
	{
		oldpwd = get_env_var_value(sh, "OLDPWD");
		if (oldpwd)
			return (ft_strdup(oldpwd));
		return (NULL);
	}
	return (NULL);
}

static char	*resolve_cd_target(t_shell *sh, char **argv)
{
	int		len;
	char	*res;

	len = 0;
	while (argv[len])
		len++;
	if (len < 2 || !argv[1])
		return (resolve_cd_special_cases(sh, NULL));
	else
	{
		res = resolve_cd_special_cases(sh, argv[1]);
		if (res)
			return (res);
		else
			return (ft_strdup(argv[1]));
	}
}

int	builtin_cd(t_shell *shell, char **argv)
{
	char	*target;
	char	oldpwd[PATH_MAX];

	if (argv[1] && argv[2])
		return (cd_error("too many arguments", NULL), 1);
	getcwd(oldpwd, PATH_MAX);
	if (!getcwd(oldpwd, PATH_MAX))
	{
		write(2, "cd: getcwd failed\n", 18);
		return (1);
	}
	target = resolve_cd_target(shell, argv);
	if (!target)
		return (cd_error("HOME not set", NULL), 1);
	if (chdir(target) != 0)
	{
		cd_error("No such file or directory", target);
		return (free(target), 1);
	}
	if (argv[1] && ft_strcmp(argv[1], "-") == 0)
		printf("%s\n", target);
	update_pwd_vars(oldpwd, shell);
	return (free(target), 0);
}
