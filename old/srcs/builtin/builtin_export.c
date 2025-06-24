/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:21:45 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/12 21:34:56 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	split_var_asin(char *arg, char **key, char **value)
// {
// 	char	*eq;

// 	eq = ft_strchr(arg, '=');
// 	if (eq)
// 	{
// 		*key = ft_strndup(arg, eq - arg);
// 		*value = ft_strdup(eq + 1);
// 	}
// 	else
// 	{
// 		*key = ft_strdup(arg);
// 		*value = ft_strdup("");
// 	}
// }

void	split_var_asin(char *arg, char **key, char **value)
{
	char	*eq;

	if (!arg)
	{
		*key = NULL;
		*value = NULL;
		return ;
	}
	eq = ft_strchr(arg, '=');
	if (eq)
	{
		*key = ft_strndup(arg, eq - arg);
		*value = ft_strdup(eq + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = ft_strdup("");
	}
	if (!*key || !*value)
	{
		free(*key);
		free(*value);
		*key = NULL;
		*value = NULL;
	}
}


void	env_set_var(char *key, char *value, t_shell *sh)
{
	t_env	*cur;
	t_env	*new;
	char	*dup_key;
	char	*dup_value;

	cur = sh->env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			dup_value = ft_strdup(value);
			if (!dup_value)
				return ;
			free(cur->value);
			cur->value = dup_value;
			return ;
		}
		cur = cur->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	dup_key = ft_strdup(key);
	dup_value = ft_strdup(value);
	if (!dup_key || !dup_value)
	{
		free(dup_key);
		free(dup_value);
		free(new);
		return ;
	}
	new->key = dup_key;
	new->value = dup_value;
	new->next = sh->env;
	sh->env = new;
}


// void	env_set_var(char *key, char *value, t_shell *sh)
// {
// 	t_env	*cur;
// 	t_env	*new;

// 	cur = sh->env;
// 	while (cur)
// 	{
// 		if (ft_strcmp(cur->key, key) == 0)
// 		{
// 			free(cur->value);
// 			cur->value = ft_strdup(value);
// 			return ;
// 		}
// 		cur = cur->next;
// 	}
// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 		return ;
// 	new->key = ft_strdup(key);
// 	new->value = ft_strdup(value);
// 	new->next = sh->env;
// 	sh->env = new;
// }


int	builtin_export(char **argv, t_shell *sh)
{
	int		i;
	int		status;
	char	*key;
	char	*value;

	i = 0;
	status = EXIT_SUCCESS;
	while (argv[i])
	{
		split_var_asin(argv[i], &key, &value);
		if (!key || !value)
		{
			perror("export: memory allocation failed");
			status = EXIT_FAILURE;
		}
		else if (!is_valid_var_name(key))
		{
			perror("export: invalid variable name");
			status = EXIT_FAILURE;
			free(key);
			free(value);
		}
		else
		{
			env_set_var(key, value, sh);
			free(key);
			free(value);
		}
		i++;
	}
	return (status);
}

// int	builtin_export(char **argv, t_shell *sh)
// {
// 	int	i;
// 	int	status;
// 	char	*key;
// 	char	*value;

// 	i = 0;
// 	status = EXIT_SUCCESS;
// 	while (argv[i])
// 	{
// 		split_var_asin(argv[i], &key, &value);
// 		if (!is_valid_var_name(key))
// 		{
// 			perror("export:");
// 			status = EXIT_FAILURE;
// 		}
// 		else
// 			env_set_var(key, value, sh);
// 		free(key);
// 		free(value);
// 		i++;
// 	}
// 	return (status);
// }