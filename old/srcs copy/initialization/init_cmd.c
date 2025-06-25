/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:42:40 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:42:44 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd   *init_cmd(void)
{
    t_cmd   *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->cmd = NULL;
    cmd->args = NULL;
    cmd->pth = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->heredoc_limiter = NULL;
    cmd->fd_in = STDIN_FILENO;
    cmd->fd_out = STDOUT_FILENO;
    cmd->heredoc = 0;
    cmd->append = 0;
    cmd->heredoc_expand = 0;
    cmd->heredoc_fd = -1;
    cmd->red = NULL;
    cmd->next = NULL;
    cmd->pid = 0;
    // cmd->quote_flag = 0;
    return (cmd);
}

void    free_cmd(t_cmd *cmd)
{
    if (!cmd)
        return ;
    free(cmd->cmd);
    free_paths(cmd->args);
    free_paths(cmd->red);
    if (cmd->heredoc && cmd->heredoc_limiter)
        free(cmd->heredoc_limiter);
    else if (cmd->infile)
        free(cmd->infile);
    if (cmd->outfile)
        free(cmd->outfile);
    free(cmd);
}

void    free_cmd_list(t_cmd *head)
{
    t_cmd   *tmp;

    if (!head)
        return ;
    while (head)
    {
        tmp = head;
        head = head->next;
        free_cmd(tmp);
    }
}
