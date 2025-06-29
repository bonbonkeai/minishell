/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:42:57 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:42:59 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_env   *add_new_node(t_env **envp, const char *key, const char *value)
// {
//     t_env *new;
//     t_env *temp;

//     new = malloc(sizeof(t_env));
//     if (!new)
//         return (NULL);
//     if (!envp)
//         return (free(new), NULL);
//     new->key = ft_strdup(key);
//     if (!new->key)
//         return (free(new), NULL);
//     if (value)
//     {    
//         new->value = ft_strdup(value);
//         if (!new->value)
//             return (free(new->key), free(new), NULL);
//     }
//     else
//         new->value = NULL;
//     new->next = NULL;
//     if (!*envp)
//         *envp = new;
//     else
//     {
//         temp = *envp;
//         while (temp->next)
//             temp = temp->next;
//         temp->next = new;
//     }
//     return (new);
// }

static t_env	*create_node(const char *key, const char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
		return (free(node), NULL);
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
			return (free(node->key), free(node), NULL);
	}
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

static void	append_node(t_env **envp, t_env *new)
{
	t_env	*temp;

	if (!*envp)
		*envp = new;
	else
	{
		temp = *envp;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

t_env	*add_new_node(t_env **envp, const char *key, const char *value)
{
	t_env	*new;

	if (!envp)
		return (NULL);
	new = create_node(key, value);
	if (!new)
		return (NULL);
	append_node(envp, new);
	return (new);
}

static int	env_list_length(t_env *env)
{
	int	count;

    count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}


t_env *init_env(char **envp)
{
    t_env *env;
    int i;
    size_t before;
    size_t after;

    env = NULL;
    i = 0;
    while (envp[i])
    {
        before = env_list_length(env);
        parse_and_add(envp[i], &env);
        after = env_list_length(env);
        if (after == before)
            return (free_env(env), NULL);
        i++;
    }
    return (env);
}




