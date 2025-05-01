#include <../minishell.h>

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
        free(env->value);
        free(env);
        env = tmp;
    }
}

char    **init_path_array(t_env *env)
{
    char *path;

    path = get_env_value(env, "PATH");
    if (!path)
        return (NULL);
    return (ft_split(path, ':'));
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