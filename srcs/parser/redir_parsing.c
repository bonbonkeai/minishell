#include <../minishell.h>

static void handle_input_redir(t_cmd *cmd, char *op, char *file)
{
    char    *tmp;

    tmp = ft_strdup(file);
    if (!tmp)
        return ;
    if (!ft_strcmp(op, "<"))
    {
        if (cmd->infile)
            free(cmd->infile);
        cmd->infile = tmp;
        cmd->heredoc = 0;
    }
    else if (!ft_strcmp(op, "<<"))
    {
        if (cmd->infile)
            free(cmd->infile);
        cmd->infile = tmp;
        cmd->heredoc = 1;
    }
}
static void handle_output_redir(t_cmd *cmd, char *op, char *file)
{
    char    *tmp;

    tmp = ft_strdup(file);
    if (!ft_strcmp(op, ">"))
    {
        if (cmd->outfile)
            free(cmd->outfile);
        cmd->outfile = tmp;
        cmd->append = 0;
    }
    else if (!ft_strcmp(op, ">>"))
    {
        if (cmd->outfile)
            free(cmd->outfile);
        cmd->outfile = tmp;
        cmd->append = 1;
    }
}

void    resolve_redir(t_cmd *cmd)
{
    int i;
    char    *op;
    char    *file;

    i = 0;
    while (cmd->red[i] && cmd->red[i + 1])
    {
        op = cmd->red[i];
        file = cmd->red[i + 1];
        handle_input_redir(cmd, op, file);
        handle_output_redir(cmd, op, file);
        i += 2;
    }
}

int is_cmd_valide(t_cmd *cmd)
{
    if (!cmd)
        return (0);
    if (!cmd->cmd || !cmd->cmd[0] == '\0')
        return (0);
    if (!cmd->args || !cmd->args[0])
        return (0);
    return (1);
}

int check_pipe(t_token *tokens)
{
    if (!tokens)
        return (0);
    if (tokens->type == T_PIPE)
        return (1);
    while (tokens)
    {
        if (tokens->type == T_PIPE && (!tokens->next) || tokens->next->type == T_PIPE)
            return (1);
        tokens = tokens->next;
    }
    return (0);
}