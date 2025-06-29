/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:46:02 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:46:04 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int expand_tab(char **tab, t_shell *sh, t_suffix_type *out_type, char *error_char)
{
    int i;
    char *expanded;
    t_suffix_type type;

    if (!tab || !sh->env || !sh || !sh->cmd)
        return (1);
    i = -1;
    //i = 0;
    while (tab[++i])
    {
        expanded = expand_string(tab[i], sh, &type, error_char);
        if (!expanded)
        {
            if (type != SUFFIX_OK)
                *out_type = type;
            //  while (i-- > 0)
            //     free(tab[i]);
            return (0);
        }
         if (tab[i] && tab[i] != expanded)
            free(tab[i]);
        tab[i] = expanded;
        // i++;
    }
    return (1);
}

// int expand_single(char **str, t_shell *sh, t_suffix_type *out_type, char *error_char)
// {
//     char *tmp[2];

//     if (!str || !*str)
//         return (1);
//     tmp[0] = ft_strdup(*str);
//     if (!tmp[0])
//         return (0);
//     tmp[1] = NULL;
//     if (!expand_tab(tmp, sh, out_type, error_char))
//     {
//         free(tmp[0]);
//         return (0);
//     }
//     free(*str);
//     *str = tmp[0];
//     return (1);
// }

int expand_vars(t_shell *sh, t_suffix_type *out_type, char *error_char)
{
    t_cmd *cmd;

    if (!sh || !sh->cmd)
        return (1);
    cmd = sh->cmd;
    while (cmd)
    {
        if (cmd->args && !expand_tab(cmd->args, sh, out_type, error_char))
            return (0);
        if (cmd->red && !expand_tab(cmd->red, sh, out_type, error_char))
            return (0);     
        cmd = cmd->next;
    }
    return (1);
}

void cleanup_current_cmd(t_shell *sh)
{
    if (!sh)
        return ;
    if (sh->cmd)
        free_cmd_list(sh->cmd);
    sh->cmd = NULL;
    if (sh->token_list)
    {
        free_tokens(sh->token_list);
        sh->token_list = NULL;
    }
    if (sh->trimmed_prompt)
    {
        free(sh->trimmed_prompt);
        sh->trimmed_prompt = NULL;
    }

}

int expand_all(t_shell *sh, t_suffix_type *out_type, char *error_char)
{
    t_cmd *cmd;

    if (!expand_vars(sh, out_type, error_char))
        return (cleanup_current_cmd(sh), 0);
    if (expand_heredoc_in_cmd_list(sh))
        return (cleanup_current_cmd(sh), 0);
    cmd = sh->cmd;
    while (cmd)
    {
        if (cmd->args && cmd->args[0])
        {
            if (cmd->cmd)
            {
                free(cmd->cmd);
                cmd->cmd = NULL;
            }
            cmd->cmd = ft_strdup(cmd->args[0]);
            if (!cmd->cmd)
                return (cleanup_current_cmd(sh), 0);
        }
        cmd = cmd->next;
    }
    return (1);
}


int has_illegal_expansion(t_suffix_type type, char ch)
{
	if (type == SUFFIX_SYNTAX_ERROR)
		ft_fprintf(2, "minishell: syntax error near unexpected token `%c'\n", ch);
	else if (type == SUFFIX_HISTORY)
		ft_fprintf(2, "minishell: !%c: event not found\n", ch);
	else if (type == SUFFIX_BACKGROUND)
		ft_fprintf(2, "minishell: `%c': command not found\n", ch);
	else if (type == SUFFIX_SEMICOLON)
		ft_fprintf(2, "minishell: command not found(unexpected `;')\n");
	else
		return (0);
	return (1);
}


