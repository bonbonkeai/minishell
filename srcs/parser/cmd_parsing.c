#include <../minishell.h>

void    add_redir(t_cmd *cmd, char *op, char *target)
{
    int len;
    char **new_red;
    int i;

    len = 0;
    while (cmd->red && cmd->red[len])
        len++;
    new_red = malloc(sizeof(char *) * (len + 3));
    if (!new_red)
        return ;
    i = 0;
    while (i < len)
    {
        new_red[i] = cmd->red[i];
        i++;
    }
    new_red[len] = ft_strdup(op);
    if (!new_red[len])
    {
        free(new_red);
        return ;
    }
    new_red[len + 1] = ft_strdup(target);
    if (!new_red[len + 1])
    {
        free(new_red[len]);
        free(new_red);
        return ;
    }
    new_red[len + 2] = NULL;
    if (cmd->red)
        free(cmd->red);
    cmd->red = new_red;
}

t_cmd   *parse_one_command(t_token **token_list)
{
    t_cmd *cmd;

    cmd = init_cmd();
    while (*token_list && (*token_list)->type != T_PIPE)
    {
        if ((*token_list)->type == T_WORD)
            add_arg(cmd, (*token_list)->content);
        else if ((*token_list)->next && (*token_list)->next->type == T_WORD)
        {
            add_redir(cmd, (*token_list)->content, (*token_list)->next->content);
            *token_list = (*token_list)->next;
        }
    }
    resolve_redir(cmd);
    if (!is_cmd_valide(cmd))
        return (free_cmd(cmd), NULL);
    return (cmd);
}

t_cmd   *parser(t_token *token_list)
{
    t_cmd   *cmd_list;
    t_cmd   *curr;
    t_cmd   *new_cmd;
   
    if (!token_list || check_pipe(token_list))
        return (ft_fprintf(stderr, "minishell: syntax error"), NULL);
    cmd_list = NULL;
    curr = NULL;
    while (token_list)
    {
        new_cmd = parse_one_command(&token_list);
        if (!new_cmd)
            return (ft_fprintf(stderr, "minishell: invalide or empty"), free_cmd(cmd_list), NULL);
        if (!cmd_list)
            cmd_list = new_cmd;
        else
            curr->next = new_cmd;
        if (token_list && token_list->type == T_PIPE)
            token_list = token_list->next;
    }
    return (cmd_list);
}
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

void    add_arg(t_cmd *cmd, const char *arg)
{
    int len;
    char **new_args;
    int i;

    len = args_len(cmd->args);
    new_args = malloc(sizeof(char *) * (len + 2));
    if (!new_args)
        return ;
    i = 0;
    while (i < len)
    {
        new_args[i] = cmd->args[i];
        i++;
    }
    new_args[i++] = ft_strdup(arg);
    if (!new_args)
    {
        free(new_args);
        return ;
    }
    new_args[i] = NULL;
    free(cmd->args);
    cmd->args = new_args;
    if (!cmd->cmd)
        cmd->cmd = ft_strdup(arg);
}