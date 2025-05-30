#include "minishell.h"

char *expand_tilde(char *input, t_env *lst_env)
{
    char *home;
    char *result;

    if (input[0] == '~')
    {
        if (!input[1] || input[1] == '/')
        {
            home = mini_get_env("HOME", lst_env);
            if (!home)
                return (free(input), NULL);
            if (!input[1])
                return (free(input), home);
            if (input[1] == '/')
            {
                result = ft_strjoin(home, input + 1);
                return (free(input), free(home), result);
            }
        }
    }
    return (input);
}

void expand_tab(char **tab, t_env *env_head, int status)
{
    int i;

    if (!tab || !env_head)
        return ;
    i = 0;
    while (tab[i])
    {
        tab[i] = expand_tilde(tab[i], env_head);
        tab[i] = expand_string(tab[i], env_head, status);
        i++;
    }
}

void expand_array(char **array, t_env *env, int status)
{
    int i;

    if (!array || !env)
        return;
    i = 0;
    while (array[i])
    {
        array[i] = expand_tilde(array[i], env);
        array[i] = expand_string(array[i], env, status);
        i++;
    }
}

void expand_all(t_cmd **cmds, t_env *env_head, int status)
{
    int i;

    if (!cmds)
        return;
    i = 0;
    while (cmds[i])
    {
        expand_array(cmds[i]->args, env_head, status);
        expand_array(cmds[i]->cmd, env_head, status);
        expand_array(cmds[i]->red, env_head, status);
        i++;
    }
}

char *expand_string(char *str, t_env *lst_env, int status)
{
    t_expansion exp;

    if (!str)
        return (NULL);
    if (str[0] == '~' && (!str[1] || str[1] == '/'))
    {
        char *home = mini_get_env("HOME", lst_env);
        if (!home)
            return (NULL);
        char *rest = ft_strdup(str + 1);
        char *joined = ft_strjoin(home, rest);
        free(rest);
        free(home);
        free(str);
        str = joined;
    }
    ft_bzero(&exp, sizeof(t_expansion));
    exp.str = str;
    exp.buf = malloc(1);
    if (!exp.buf)
        return (NULL);
    exp.buf[0] = '\0';
    while (exp.str[exp.i])
    {
        if (exp.str[exp.i] == '\'')
            handle_single_quote(&exp);
        else if (exp.str[exp.i] == '\"')
            handle_double_quote(&exp, lst_env, status);
        else if (exp.str[exp.i] == '$')
        {
            if (!handle_dollar(exp.str, &exp, lst_env, status))
                return (free(exp.buf), NULL);
        }
        else
            append_char(&exp, exp.str[exp.i++]);
    }
    return (exp.buf);
}



