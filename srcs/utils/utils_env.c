/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:06:39 by jinhuang          #+#    #+#             */
/*   Updated: 2025/07/02 19:25:17 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_value(t_env *cur, const char *value)
{
	char	*new_val;

	new_val = ft_strjoin(cur->value, value);
	if (!new_val)
		return ;
	free(cur->value);
	cur->value = new_val;
}

static void	replace_value(t_env *cur, const char *value)
{
	char	*dup;

	dup = ft_strdup(value);
	if (!dup)
		return ;
	free(cur->value);
	cur->value = dup;
}

static t_env	*create_new_env_node(const char *key, const char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->exported = 0;
	new->next = NULL;
	if (!new->key || !new->value)
	{
		free(new->key);
		free(new->value);
		free(new);
		return (NULL);
	}
	return (new);
}

static t_env	*find_env_node(t_env *env, char *key)
{
	t_env	*cur;

	cur = env;
	if (!cur)
		return (NULL);
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (cur);
		if (!cur->next)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

void	env_set_value(t_shell *sh, char *key, char *value, int append)
{
	t_env	*node;
	t_env	*cur;
	t_env	*new;

	if (!value)
		value = "";
	node = find_env_node(sh->env, key);
	if (node && ft_strcmp(node->key, key) == 0)
	{
		if (append)
			append_value(node, value);
		else
			replace_value(node, value);
		return ;
	}
	cur = node;
	new = create_new_env_node(key, value);
	if (!new)
		return ;
	if (!cur)
		sh->env = new;
	else
		cur->next = new;
}
