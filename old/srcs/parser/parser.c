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

t_cmd *parser(t_token *token_list)
{
    t_cmd *cmd_list;
    t_cmd *curr;
    t_cmd *new_cmd;

    cmd_list = NULL;
    curr = NULL;
    new_cmd = NULL;
    if (!token_list)
        return (NULL);
    if (check_pipe(token_list))
        return (NULL);
    while (token_list)
    {
        new_cmd = parse_one_command(&token_list);
        if (!new_cmd)
        {
            ft_fprintf(2, "minishell: invalide or empty");
            free_cmd_list(cmd_list);
            return (NULL);
        }
        if (!cmd_list)
        {
            cmd_list = new_cmd;
            curr = new_cmd;
        }
        else
        {
            curr->next = new_cmd;
            curr = new_cmd;
        }
        if (token_list && token_list->type == T_PIPE)
        {
            token_list = token_list->next;
        }
    }
    return (cmd_list);
}

int check_pipe(t_token *tokens)
{
    if (!tokens)
        return (0);
    if (tokens->type == T_PIPE)
        return (1);
    while (tokens)
    {
        if (tokens->type == T_PIPE && (!tokens->next || tokens->next->type == T_PIPE))
            return (1);
        tokens = tokens->next;
    }
    return (0);
}

t_cmd *parse_one_command(t_token **token_list)
{
    t_cmd *cmd;
    
    cmd = init_cmd();
    if (!cmd)
        return (NULL);
    while (*token_list && (*token_list)->type != T_PIPE)
    {
        if ((*token_list)->type == T_WORD)
            add_arg(cmd, (*token_list)->content);
        else if (is_red_type((*token_list)->type)
                 && (*token_list)->next
                 && (*token_list)->next->type == T_WORD)
        {
            add_redir(cmd, (*token_list)->content, (*token_list)->next->content);
            *token_list = (*token_list)->next;
        }
        *token_list = (*token_list)->next;
    }
    resolve_redir(cmd);
    if (!is_cmd_valide(cmd))
    {
        free_cmd(cmd);
        return (NULL);
    }
    return (cmd);
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

void add_arg(t_cmd *cmd, const char *arg)
{
    int len;
    char **new_args;
    int i;

    if (!arg || !arg[0])
        return ;
    len = args_len(cmd->args);
    new_args = malloc(sizeof(char *) * (len + 2));
    if (!new_args)
        return ;
    i = 0;
    while (i < len)
    {
        new_args[i] = ft_strdup(cmd->args[i]);
        if (!new_args[i])
        {
            while (--i >= 0)
                free(new_args[i]);
            free(new_args);
            return ;
        }
        i++;
    }
    new_args[i++] = ft_strdup(arg);
    if (!new_args[i - 1])
    {
	    free(new_args);
	    return ;
    }
    new_args[i] = NULL;
    free_paths(cmd->args);
    cmd->args = new_args;
    if (!cmd->cmd)
        cmd->cmd = ft_strdup(arg);
}

int is_cmd_valide(t_cmd *cmd)
{
    if (!cmd)
        return (0);
    if (!cmd->cmd || cmd->cmd[0] == '\0')
        return (0);
    if (!cmd->args || !cmd->args[0])
        return (0);
    return (1);
}