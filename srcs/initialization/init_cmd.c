#include "minishell.h"

t_cmd   *init_cmd(void)
{
    t_cmd   *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->cmd = NULL;
    cmd->args = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->heredoc = 0;
    cmd->append = 0;
    cmd->heredoc_expand = 0;
    cmd->heredoc_fd = 0;
    cmd->red = NULL;
    cmd->next = NULL;
    return (cmd);
}

void    free_cmd(t_cmd *cmd)
{
    if (!cmd)
        return ;
    free(cmd->cmd);
    free_paths(cmd->args);
    free_paths(cmd->red);
    if (cmd->infile)
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