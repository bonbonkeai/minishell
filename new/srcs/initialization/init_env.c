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

t_env   *add_new_node(t_env **envp, const char *key, const char *value)
{
    t_env *new;
    t_env *temp;

    new = malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    if (!envp)
        return (free(new), NULL);
    new->key = ft_strdup(key);
    if (!new->key)
        return (free(new), NULL);
    if (value)
    {    
        new->value = ft_strdup(value);
        if (!new->value)
            return (free(new->key), free(new), NULL);
    }
    else
        new->value = NULL;
    new->next = NULL;
    if (!*envp)
        *envp = new;
    else
    {
        temp = *envp;
        while (temp->next)
            temp = temp->next;
        temp->next = new;
    }
    return (new);
}

// t_env   *init_env(char **envp)
// {
//     t_env *env;
//     int i;

//     i = 0;
//     env = NULL;
//     while (envp[i])
//     {
//         parse_and_add(envp[i], &env);
//         i++;   
//     }
//     return (env);
// }

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
    t_env *env = NULL;
    int i = 0;
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
        {
            free_env(env);
            return (NULL);
        }
        i++;
    }
    return (env);
}

void    parse_and_add(char *entry, t_env **env)
{
    char *sep;
    char *key;
    char *value;
    size_t key_len;

    sep = ft_strchr(entry, '=');
    if (!sep)
        return ;
    key_len = sep - entry;
    key = ft_strndup(entry, key_len);
    value = ft_strdup(sep + 1);
    if (!key || !value || !add_new_node(env, key, value))
    {
        if (key)
            free(key);
        if (value)
            free(value);
        return ;
    }
    // if (!add_new_node(env, key, value))
    // {
    //     free(key);
    //     free(value);
    //     return ;
    // }
    else
    {
        free(key);
        free(value);
    }
}

// void    handle_empty_env(t_env **env)
// {
//     char cwd[PATH_MAX];

//     if (!*env)
//     {
//         if (getcwd(cwd, PATH_MAX))
//             add_new_node(env,  "SHLVL", "1");
//         add_new_node(env, "PATH", "/usr/bin:/bin");
//         add_new_node(env, "HOME", "/tmp");
//     }
// }

void    handle_empty_env(t_env **env)
{
    char cwd[PATH_MAX];

    if (!*env)
    {
        if (getcwd(cwd, PATH_MAX))
        {
            if (!add_new_node(env, "SHLVL", "1"))
            {
                free_env(*env);
                *env = NULL;
                return ;
            }
        }
        if (!add_new_node(env, "PATH", "/usr/bin:/bin"))
        {
            free_env(*env);
            *env = NULL;
            return ;
        }
        if (!add_new_node(env, "HOME", "/tmp"))
        {
            free_env(*env);
            *env = NULL;
            return ;
        }
    }
}


char *extract_username(t_env *env)
{
    char *user;

    user = get_env_value(env, "USER");
    if (user)
        return (ft_strdup(user));
    return (ft_strdup("guest"));
}

