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

t_shell *init_shell(char **envp)
{
    t_shell *sh;

    sh = malloc(sizeof(t_shell));
    if (!sh)
        return (NULL);
    sh->env = init_env(envp);
    handle_empty_env(&sh->env);
    sh->username = extract_username(sh->env);
    sh->paths = init_path_array(sh->env);
    sh->trimmed_prompt = NULL;
    sh->status = 0;
    sh->old_pipe.fd[0] = -1;
    sh->old_pipe.fd[1] = -1;
    sh->new_pipe.fd[0] = -1;
    sh->new_pipe.fd[1] = -1;
    sh->cmd = init_cmd();
    return (sh);
}

void    free_shell(t_shell *sh)
{
    if (!sh)
        return ;
    if (sh->env)
        free_env(sh->env);
    if (sh->paths)
        free_paths(sh->paths);
    if (sh->username)
        free(sh->username);
    if (sh->trimmed_prompt)
		free(sh->trimmed_prompt);
    if (sh->cmd)
    {
        free_cmd_list(sh->cmd);
        sh->cmd = NULL;
    }
    free(sh);
}

