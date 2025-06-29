
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:47:32 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:47:34 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void cleanup_and_exit(t_shell *sh, int error_status)
{
    if (sh->token_list)
    {
        free_tokens(sh->token_list);
        sh->token_list = NULL;
    }
    if (sh->cmd)
    { 
        free_cmd_list(sh->cmd);
        sh->cmd = NULL;
    }
    sh->curr_cmd = NULL;
    if (sh->trimmed_prompt)
    {
        free(sh->trimmed_prompt);
        sh->trimmed_prompt = NULL;
    }
    sh->status = error_status;
}

// void process_input(t_shell *sh, char *input)
// {
//     t_suffix_type illegal_type;
//     char error_char;
//     t_cmd *cmd;

//     illegal_type = SUFFIX_OK;
//     error_char = 0;
//     sh->trimmed_prompt = ft_strtrim(input, " \t\n");
//     if (!sh->trimmed_prompt || sh->trimmed_prompt[0] == '\0')
//     {
//         free(sh->trimmed_prompt);
//         sh->trimmed_prompt = NULL;
//         return ;
//     }
//     if (!lexer(sh))
//         return (cleanup_and_exit(sh, 2));
//     if (sh->token_list)
//     {
//         free_tokens(sh->token_list);
//         sh->token_list = NULL;
//     }
//     tokenize_prompt(sh, sh->trimmed_prompt);
//     if (!sh->token_list)
//         return (cleanup_and_exit(sh, 2));
//     if (check_token_syntax(sh->token_list))
//         return (cleanup_and_exit(sh, 2));
//     cmd = sh->cmd;
//     cmd = parser(sh);
//     if (!cmd)
//         return (cleanup_and_exit(sh, 2));
//     sh->cmd = cmd;
//     if (!expand_all(sh, &illegal_type, &error_char))
//     {
//         has_illegal_expansion(illegal_type, error_char);
//         return (cleanup_and_exit(sh, 2));
//     }
//     sh->curr_cmd = sh->cmd;
//     if (sh->cmd)
//         sh->status = executor(sh);
//     cleanup_and_exit(sh, sh->status);
// }

static bool lexer_input(t_shell *sh, char *input)
{
    sh->trimmed_prompt = ft_strtrim(input, " \t\n");
    if (!sh->trimmed_prompt || sh->trimmed_prompt[0] == '\0')
    {
        free(sh->trimmed_prompt);
        sh->trimmed_prompt = NULL;
        return (false);
    }
    if (!lexer(sh))
    {
        cleanup_and_exit(sh, 2);
        return (false);
    }
    return (true);
}

static bool tokenize_and_parse(t_shell *sh)
{
    if (sh->token_list)
    {
        free_tokens(sh->token_list);
        sh->token_list = NULL;
    }
    tokenize_prompt(sh, sh->trimmed_prompt);
    if (!sh->token_list || check_token_syntax(sh->token_list))
    {
        cleanup_and_exit(sh, 2);
        return (false);
    }
    return (true);
}

static bool expand_and_check(t_shell *sh, t_suffix_type *illegal_type, char *error_char)
{
    if (!expand_all(sh, illegal_type, error_char))
    {
        has_illegal_expansion(*illegal_type, *error_char);
        cleanup_and_exit(sh, 2);
        return (false);
    }
    return (true);
}

void process_input(t_shell *sh, char *input)
{
    t_suffix_type illegal_type;
    char error_char;
    t_cmd *cmd;

    illegal_type = SUFFIX_OK;
    error_char = 0;
    if (!lexer_input(sh, input))
        return ;
    if (!tokenize_and_parse(sh))
        return ;
    cmd = parser(sh);
    if (!cmd)
        return (cleanup_and_exit(sh, 2));
    sh->cmd = cmd;
    if (!expand_and_check(sh, &illegal_type, &error_char))
        return ;
    sh->curr_cmd = sh->cmd;
    if (sh->cmd)
        sh->status = executor(sh);
    cleanup_and_exit(sh, sh->status);
}
