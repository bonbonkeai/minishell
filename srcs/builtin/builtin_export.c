/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:21:45 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/03 16:55:06 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_set_exported(t_shell *sh, char *key, int exported)
{
	t_env	*cur;

	cur = sh->env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			cur->exported = exported;
			return ;
		}
		cur = cur->next;
	}
}

static int	env_has_var(char *key, t_shell *sh)
{
	t_env	*env;

	env = sh->env;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

static int	process_export_arg(t_shell *sh, char *arg)
{
	char	*key;
	char	*value;
	int		append;

	split_var_asin(arg, &key, &value, &append);
	if (!key || !value)
		return (perror(ERRMAL), EXIT_FAILURE);
	if (!is_valid_var_name(key))
	{
		ft_perror_export(arg);
		return (free(key), free(value), EXIT_FAILURE);
	}
	if (ft_strchr(arg, '=') == NULL)
	{
		if (!env_has_var(key, sh))
			env_set_value(sh, key, value, append);
	}
	else
	{
		env_set_value(sh, key, value, append);
		env_set_exported(sh, key, 1);
	}
	return (free(key), free(value), EXIT_SUCCESS);
}

int	builtin_export(char **argv, t_shell *sh)
{
	int	i;
	int	status;

	i = 1;
	status = EXIT_SUCCESS;
	if (!argv[1])
	{
		export_print_env(sh);
		return (status);
	}
	if (argv[1][0] == '-')
	{
		if (argv[1][1] != 'f' && argv[1][1] != 'n' && argv[1][1] != '\0')
		{
			ft_printf("bash: export: -%c: invalid option\n", argv[1][1]);
			ft_printf(MES_E);
			return (EXIT_FAILURE);
		}
	}
	while (argv[i++])
	{
		if (process_export_arg(sh, argv[i - 1]) == EXIT_FAILURE)
			status = EXIT_FAILURE;
	}
	return (status);
}
