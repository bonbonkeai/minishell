/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:43:25 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:43:28 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_value(t_env *env, const char *key)
{
    if (!env)
        return (NULL);
    while (env)
    {
        if (strcmp(env->key, key) ==  0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

void    free_env(t_env *env)
{
    t_env *tmp;

    while (env)
    {
        tmp = env->next;
        free(env->key);
        env->key = NULL;
        free(env->value);
        env->value = NULL;
        free(env);
        env = tmp;
    }
}


char **init_path_array(t_env *env)
{
    char *path;
    char **split;

    path = get_env_value(env, "PATH");
    if (!path)
        return (NULL);
    split = ft_split(path, ':');
    if (!split)
        return (NULL);
    return (split);
}

void    free_paths(char **paths)
{
    int i;

    i = 0;
    if (!paths)
        return ;
    while (paths[i])
        free(paths[i++]);
    free(paths);
}

char *extract_username(t_env *env)
{
    char *user;

    user = get_env_value(env, "USER");
    if (user)
        return (ft_strdup(user));
    return (ft_strdup("guest"));
}