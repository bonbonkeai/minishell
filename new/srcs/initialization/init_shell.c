/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:43:37 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:43:41 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_shell *init_shell(char **envp)
// {
//     t_shell *sh;

//     sh = malloc(sizeof(t_shell));
//     if (!sh)
//         return (NULL);
//     sh->env = init_env(envp);
//     if (!sh->env)
//         return (free(sh), NULL);
//     handle_empty_env(&sh->env);
//     if (!sh->env)
//          return (free(sh), NULL);
//     sh->username = extract_username(sh->env);
//     if (!sh->username)
//         return (free_env(sh->env), free(sh), NULL);
//     sh->paths = init_path_array(sh->env);
//     if (!sh->paths)
//         return (free(sh->username), free_env(sh->env), free(sh), NULL);
//     sh->trimmed_prompt = NULL;
//     sh->status = 0;
//     sh->old_pipe.fd[0] = -1;
//     sh->old_pipe.fd[1] = -1;
//     sh->new_pipe.fd[0] = -1;
//     sh->new_pipe.fd[1] = -1;
//     sh->cmd = NULL;
//     sh->token_list = NULL;
//     sh->curr_cmd = NULL;
//     return (sh);
// }


static int init_shell_env(t_shell *sh, char **envp)
{
    sh->env = init_env(envp);
    if (!sh->env)
        return (free(sh), 0);
    handle_empty_env(&sh->env);
    if (!sh->env)
        return (free(sh), 0);
    sh->username = extract_username(sh->env);
    if (!sh->username)
        return (free_env(sh->env), free(sh), 0);
    sh->paths = init_path_array(sh->env);
    if (!sh->paths)
    {
        free(sh->username);
        free_env(sh->env);
        free(sh);
        return (0);
    }
    return (1);
}

static void init_shell_fields(t_shell *sh)
{
    sh->trimmed_prompt = NULL;
    sh->status = 0;
    sh->old_pipe.fd[0] = -1;
    sh->old_pipe.fd[1] = -1;
    sh->new_pipe.fd[0] = -1;
    sh->new_pipe.fd[1] = -1;
    sh->cmd = NULL;
    sh->token_list = NULL;
    sh->curr_cmd = NULL;
}


t_shell *init_shell(char **envp)
{
    t_shell *sh;

    sh = malloc(sizeof(t_shell));
    if (!sh)
        return (NULL);
    if (!init_shell_env(sh, envp))
        return (NULL);
    init_shell_fields(sh);
    return (sh);
}

// void    free_shell(t_shell *sh)
// {
//     if (!sh)
//         return ;
   
//     free_env(sh->env);
//     sh->env = NULL;
//     free_paths(sh->paths);
//     sh->paths = NULL;
//     free(sh->username);
//     sh->username = NULL;
// 	free(sh->trimmed_prompt);
//     sh->trimmed_prompt = NULL;
//     if (sh->token_list)
//     {
//         free_tokens(sh->token_list);
//         sh->token_list = NULL;
//     }
//     if (sh->cmd)
//     {
//         free_cmd_list(sh->cmd);
//         sh->cmd = NULL;
//         sh->curr_cmd = NULL;
//     }
//     free(sh);
// }


static void free_shell_env(t_shell *sh)
{
    free_env(sh->env);
    sh->env = NULL;
    free_paths(sh->paths);
    sh->paths = NULL;
    if (sh->username)
    {   
        free(sh->username);
        sh->username = NULL;
    }
    if (sh->trimmed_prompt)
    {
        free(sh->trimmed_prompt);
        sh->trimmed_prompt = NULL;
    }
}

void free_shell(t_shell *sh)
{
    if (!sh)
        return ;
    free_shell_env(sh);
    if (sh->token_list)
    {
        free_tokens(sh->token_list);
        sh->token_list = NULL;
    }
    if (sh->cmd)
    {
        free_cmd_list(sh->cmd);
        sh->cmd = NULL;
        sh->curr_cmd = NULL;
    }
    free(sh);
}