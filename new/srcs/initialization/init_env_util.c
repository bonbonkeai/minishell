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
    free(key);
    free(value);
}

// void    handle_empty_env(t_env **env)
// {
//     char cwd[PATH_MAX];

//     if (!*env)
//     {
//         if (getcwd(cwd, PATH_MAX))
//         {
//             if (!add_new_node(env, "SHLVL", "1"))
//             {
//                 free_env(*env);
//                 *env = NULL;
//                 return ;
//             }
//         }
//         if (!add_new_node(env, "PATH", "/usr/bin:/bin"))
//         {
//             free_env(*env);
//             *env = NULL;
//             return ;
//         }
//         if (!add_new_node(env, "HOME", "/tmp"))
//         {
//             free_env(*env);
//             *env = NULL;
//             return ;
//         }
//     }
// }

static int add_shlvl_if_possible(t_env **env)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX))
    {
        if (!add_new_node(env, "SHLVL", "1"))
        {
            free_env(*env);
            *env = NULL;
            return (0);
        }
    }
    return (1);
}

static int add_default_path(t_env **env)
{
    if (!add_new_node(env, "PATH", "/usr/bin:/bin"))
    {
        free_env(*env);
        *env = NULL;
        return (0);
    }
    return (1);
}

static int add_default_home(t_env **env)
{
    if (!add_new_node(env, "HOME", "/tmp"))
    {
        free_env(*env);
        *env = NULL;
        return (0);
    }
    return (1);
}

void handle_empty_env(t_env **env)
{
    if (!*env)
    {
        if (!add_shlvl_if_possible(env))
            return ;
        if (!add_default_path(env))
            return ;
        if (!add_default_home(env))
            return ;
    }
}
