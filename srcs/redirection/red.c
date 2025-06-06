#include "minishell.h"

void handle_input_redir(t_cmd *cmd, char *op, char *file)
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
        //cmd->fd_in = -1;
        cmd->heredoc = 0;
    }
    else if (!ft_strcmp(op, "<<"))
    {
        if (cmd->infile)
            free(cmd->infile);
        cmd->infile = tmp;
        cmd->heredoc = 1;
        if ((file[0] == '\'' && file[ft_strlen(file) - 1] == '\'') ||
			(file[0] == '"' && file[ft_strlen(file) - 1] == '"'))
			cmd->heredoc_expand = 0;
		else
			cmd->heredoc_expand = 1;
    }
}

void handle_output_redir(t_cmd *cmd, char *op, char *file)
{
    char    *tmp;

    tmp = ft_strdup(file);
    if (!ft_strcmp(op, ">"))
    {
        if (cmd->outfile)
            free(cmd->outfile);
        cmd->outfile = tmp;
        //cmd->fd_out = -1;
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

void resolve_redir(t_cmd *cmd)
{
    int i;
    char *op;
    char *file;

    i = 0;
    if (!cmd)
        return ;
    if (!cmd->red)
        return ;
    while (cmd->red[i] && cmd->red[i + 1])
    {
        op = cmd->red[i];
        file = cmd->red[i + 1];
        handle_input_redir(cmd, op, file);
        handle_output_redir(cmd, op, file);
        i += 2;
    }
}

void    add_redir(t_cmd *cmd, char *op, char *target)
{
    int len;
    char **new_red;
    int i;
    int j;

    if (!op || !target)
    {
        ft_fprintf(2, "minishell: syntax error near unexpected token\n");
        return ;
    }
    len = 0;
    while (cmd->red && cmd->red[len])
        len++;
    new_red = malloc(sizeof(char *) * (len + 3));
    if (!new_red)
        return ;
    i = 0;
    while (i < len)
    {
        new_red[i] = ft_strdup(cmd->red[i]);
        if (!new_red[i])
        {
            while (--i >= 0)
                free(new_red[i]);
            free(new_red);
            return ;
        }
        i++;
    }
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
    {
        j = 0;
        while (cmd->red[j])
            free(cmd->red[j++]);
        free(cmd->red);
    }
    cmd->red = new_red;
}