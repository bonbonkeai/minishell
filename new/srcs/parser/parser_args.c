/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:44:37 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:44:38 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int args_len(char **args)
{
    int i;

    i = 0;
    if (!args)
        return (0);
    while (args[i])
        i++;
    return (i);
} 

// void add_arg(t_cmd *cmd, const char *arg)
// {
//     int len;
//     char **new_args;
//     int i;

//     if (!arg || !arg[0])
//         return ;
//     len = args_len(cmd->args);
//     new_args = malloc(sizeof(char *) * (len + 2));
//     if (!new_args)
//         return ;
//     i = 0;
//     while (i < len)
//     {
//         new_args[i] = ft_strdup(cmd->args[i]);
//         if (!new_args[i])
//         {
//             while (--i >= 0)
//                 free(new_args[i]);
//             free(new_args);
//             return ;
//         }
//         i++;
//     }
//     new_args[i++] = ft_strdup(arg);
//     // if (!new_args[i - 1])
//     // {
// 	//     free(new_args);
// 	//     return ;
//     // }
//     if (!new_args[i - 1])
//     {
//         while (--i >= 0)
//             free(new_args[i]);
//         free(new_args);
//         return;
//     }
//     new_args[i] = NULL;
//     free_paths(cmd->args);
//     cmd->args = new_args;
//     if (!cmd->cmd)
//         cmd->cmd = ft_strdup(arg);
// }

void add_arg(t_cmd *cmd, const char *arg)
{
    int len;
    char **new_args;

    if (!arg || !arg[0])
        return ;
    len = args_len(cmd->args);
    new_args = duplicate_args(cmd->args, len, arg);
    if (!new_args)
        return ;
    free_paths(cmd->args);
    cmd->args = new_args;
    if (!cmd->cmd)
        cmd->cmd = ft_strdup(arg);
}

int copy_old_args(char **dest, char **src, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        dest[i] = ft_strdup(src[i]);
        if (!dest[i])
        {
            while (--i >= 0)
                free(dest[i]);
            return (0);
        }
        i++;
    }
    return (1);
}

char **duplicate_args(char **old_args, int len, const char *arg)
{
    char **new_args;
    int i;

    new_args = malloc(sizeof(char *) * (len + 2));
    if (!new_args)
        return (NULL);
    if (!copy_old_args(new_args, old_args, len))
        return (free(new_args), NULL);
    i = len;
    new_args[i++] = ft_strdup(arg);
    if (!new_args[i - 1])
    {
        while (--i >= 0)
            free(new_args[i]);
        free(new_args);
        return (NULL);
    }
    new_args[i] = NULL;
    return (new_args);
}

// int is_cmd_valide(t_cmd *cmd)
// {
//     if (!cmd)
//         return (0);
//     if (!cmd->cmd || cmd->cmd[0] == '\0')
//         return (0);
//     if (!cmd->args || !cmd->args[0])
//         return (0);
//     return (1);
// }
int is_cmd_valide(t_cmd *cmd) 
{
    if (!cmd)
        return (0);
    if (cmd->cmd && cmd->cmd[0] != '\0' &&
        cmd->args && cmd->args[0] != NULL)
        return (1);
    if (cmd->heredoc_limiter || cmd->infile || cmd->outfile)
        return (1);
    return (0);
}
