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

// t_cmd *parser(t_shell *sh)
// {
//     t_token *token_list;
//     t_cmd *cmd_list;
//     t_cmd *curr;
//     t_cmd *new_cmd;

//     token_list = sh->token_list;
//     cmd_list = NULL;
//     curr = NULL;
//     new_cmd = NULL;
//     if (!token_list)
//         return (NULL);
//     if (check_pipe(token_list))
//         return (NULL);
//     while (token_list)
//     {
//         new_cmd = parse_one_command(&token_list);
//         if (!new_cmd)
//         {
//             ft_fprintf(2, "minishell: invalide or empty\n");
//             free_cmd_list(cmd_list);
//             return (NULL);
//         }
//         if (!cmd_list)
//         {
//             cmd_list = new_cmd;
//             curr = new_cmd;
//         }
//         else
//         {
//             curr->next = new_cmd;
//             curr = new_cmd;
//         }
//         if (token_list && token_list->type == T_PIPE)
//             token_list = token_list->next;
//     }
//     return (cmd_list);
// }

t_cmd *parser(t_shell *sh)
{
    t_token *token_list;

    token_list = sh->token_list;
    if (!token_list || check_pipe(token_list))
        return (NULL);
    return (build_cmd_list(token_list));
}

t_cmd *build_cmd_list(t_token *token_list)
{
    t_cmd *cmd_list;
    t_cmd *curr;
    t_cmd *new_cmd;

    cmd_list = NULL;
    curr = NULL;
    while (token_list)
    {
        new_cmd = parse_one_command(&token_list);
        if (!new_cmd)
        {
            ft_fprintf(2, "minishell: invalide or empty\n");
            return (free_cmd_list(cmd_list), NULL);
        }
        if (!cmd_list)
            cmd_list = curr = new_cmd;
        else
            curr = curr->next = new_cmd;
        if (token_list && token_list->type == T_PIPE)
            token_list = token_list->next;
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

// t_cmd *parse_one_command(t_token **token_list)
// {
//     t_cmd *cmd;
    
//     cmd = init_cmd();
//     if (!cmd)
//         return (NULL);
//     while (*token_list && (*token_list)->type != T_PIPE)
//     {
//         if ((*token_list)->type == T_WORD)
//             add_arg(cmd, (*token_list)->content);
//         else if (is_red_type((*token_list)->type)
//                  && (*token_list)->next
//                  && (*token_list)->next->type == T_WORD)
//         {
//             add_redir(cmd, (*token_list)->content, (*token_list)->next->content);
//             *token_list = (*token_list)->next;
//         }
//         *token_list = (*token_list)->next;
//     }
//     // resolve_redir(cmd);
//     if (!is_cmd_valide(cmd))
//     {
//         free_cmd(cmd);
//         return (NULL);
//     }
//     return (cmd);
// }

t_cmd *parse_one_command(t_token **token_list)
{
	t_cmd *cmd;

	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	while (*token_list && (*token_list)->type != T_PIPE)
	{
		if (!handle_token(cmd, token_list))
			return (free_cmd(cmd), NULL);
	}
	if (!is_cmd_valide(cmd))
		return (free_cmd(cmd), NULL);
	return (cmd);
}

bool handle_token(t_cmd *cmd, t_token **token_list)
{
	t_token *curr;

	curr = *token_list;
	if (curr->type == T_WORD)
		add_arg(cmd, curr->content);
	else if (is_red_type(curr->type)
		&& curr->next && curr->next->type == T_WORD)
	{
		add_redir(cmd, curr->content, curr->next->content);
		*token_list = curr->next;
	}
	else if (is_red_type(curr->type))
		return (false);
	*token_list = (*token_list)->next;
	return (true);
}


