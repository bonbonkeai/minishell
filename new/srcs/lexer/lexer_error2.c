/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:43:58 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:44:02 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_too_many_redir(const char *input, int i)
{
    if (is_too_many_char(input, i, '>'))
        return (syntax_error_pipex(">>"), TRUE);
    if (is_too_many_char(input, i, '<'))
        return (syntax_error_pipex("<<"), TRUE);
    return (FALSE);
}
  
int check_spacing_errors(const char *input, int i)
{
    // case: '>> >>' → token '>>'
    if (input[i] == '>' && input[i + 1] == '>' &&
        next_non_space(input, i + 1) == '>')
        return (syntax_error_pipex(">>"), TRUE);  
    else if (input[i] == '<' && input[i + 1] == '<' &&
        next_non_space(input, i + 1) == '<')
        return (syntax_error_pipex("<<"), TRUE);
    // case: '> >' → token '>'
    if (input[i] == '>' && input[i + 1] != '>' &&
        next_non_space(input, i) == '>')
        return (syntax_error_pipex(">"), TRUE);
    // case: '< <' → token '<'
    if (input[i] == '<' && input[i + 1] != '<' && next_non_space(input, i) == '<')
        return (syntax_error_pipex("<"), TRUE);
    if ((input[i] == '>' || input[i] == '<') &&
        next_non_space(input, i) == '<' &&
        !(input[i] == '<' && input[i + 1] == '<'))
        return (syntax_error_pipex("<"), TRUE);
    return (FALSE);
}

int check_double_pipe(const char *input, int i)
{
    if (input[i] == '|' && input[i + 1] == '|')
        return (syntax_error_pipex("||"), TRUE);
    if (input[i] == '|' && next_non_space(input, i) == '|')
        return (syntax_error_pipex("|"), TRUE);
    return (FALSE);
}

int check_mixed_combos(const char *input, int i)
{
    //case: mixed invalid combos
    if (input[i] == '>' && input[i + 1] == '<')
        return (syntax_error_pipex("<"), TRUE);
    if (input[i] == '<' && input[i + 1] == '>')
        return (syntax_error_newline(), TRUE);
    return (FALSE);
}

int is_invalid_operator(const char *input, int i)
{
    if (check_heredoc_redir_conflict(input, i))
        return (TRUE);
    if (check_long_redir_sequence(input, i))
        return (TRUE);
    if (check_pipe_conflict(input, i))
        return (TRUE);
    if (check_redir_newline_end(input, i))
        return (TRUE);
    if (check_triple_redir(input, i))
        return (TRUE);
    if (check_too_many_redir(input, i))
        return (TRUE);
    if (check_spacing_errors(input, i))
        return (TRUE);
    if (check_double_pipe(input, i))
        return (TRUE);
    if (check_mixed_combos(input, i))
        return (TRUE);
    return (FALSE);
}

// int is_invalid_operator(const char *input, int i)
// {
//     //echo << >> → 应报错 >> 而非 newline
//     int j;
//     int count;

//     if (input[i] == '<' && input[i + 1] == '<')
// 	{
// 		j = i + 2;
// 		while (input[j] && ft_isspace(input[j]))
// 			j++;
// 		if (input[j] == '>' && input[j + 1] == '>')
// 			return (syntax_error_pipex(">>"), TRUE);
// 	}
//     if (input[i] == '<')
// 	{
// 		count = 0;
// 		while (input[i + count] == '<')
// 			count++;
// 		if (count > 3)
// 		{
// 			if (count > 5)
// 				return (syntax_error_pipex("<<<"), TRUE);
// 			else
// 				return (syntax_error_pipex("<<"), TRUE);
// 		}
// 	}
//     //

//     // case: >>|><
//     if ((input[i] == '>' || input[i] == '<') && input[i + 1] == input[i] && input[i + 1] == '|')
//         return (syntax_error_pipex("|"), TRUE);

//     if ((input[i] == '>' || input[i] == '<') &&
// 		input[i + 1] == '|')
// 		return (syntax_error_pipex("|"), TRUE);
 
//     // case: end with redirection without file
//     if ((input[i] == '>' || input[i] == '<') && input[i + 1] == '\0')
//         return (syntax_error_newline(), TRUE);

//     //cat >>> ; cat <<< ; cat << ; cat >>
//     if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>' && input[i + 3] != '>')
//         return (syntax_error('>'), TRUE);
//     else if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<' && input[i + 3] != '<')
//         return (syntax_error_newline(), TRUE);
//     if ((input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<' && input[i + 3] != '<') ||
//     (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>' && input[i + 3] != '>'))
//         return (syntax_error_newline(), TRUE);
//     if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<' && input[i + 3] != '<')
//         return (syntax_error_newline(), TRUE);

//     //>>>>> ; <<<<<<
//     if (is_too_many_char(input, i, '>'))
//         return (syntax_error_pipex(">>"), TRUE);
//     if (is_too_many_char(input, i, '<'))
//         return (syntax_error_pipex("<<"), TRUE);

//     // case: '>> >>' → token '>>'
//     if (input[i] == '>' && input[i + 1] == '>' &&
//         next_non_space(input, i + 1) == '>')
//         return (syntax_error_pipex(">>"), TRUE);
//     // case: '> >' → token '>'
//     if (input[i] == '>' && input[i + 1] != '>' &&
//         next_non_space(input, i) == '>')
//     {
//         syntax_error_pipex(">");
//         return (TRUE);
//     }
//     // case: '< <' → token '<'
//     if (input[i] == '<' && input[i + 1] != '<' && next_non_space(input, i) == '<')
//         return (syntax_error_pipex("<"), TRUE);

//     // case: echo > < → token '<'
//     if ((input[i] == '>' || input[i] == '<') &&
//         next_non_space(input, i) == '<' &&
//         !(input[i] == '<' && input[i + 1] == '<'))
//         return (syntax_error_pipex("<"), TRUE);

//     // case: double pipes (||)
//     if (input[i] == '|' && input[i + 1] == '|')
//         return (syntax_error_pipex("||"), TRUE);

//     // case: echo | | → token '|'
//     if (input[i] == '|' && next_non_space(input, i) == '|')
//         return (syntax_error_pipex("|"), TRUE);

//     // case: mixed invalid combos
//     if (input[i] == '>' && input[i + 1] == '<')
//         return (syntax_error_pipex("<"), TRUE);

//     // if (input[i] == '<' && input[i + 1] == '>')
//     //     return (syntax_error_pipex(">"), TRUE);

//     if (input[i] == '<' && input[i + 1] == '>')
//         return (syntax_error_newline(), TRUE);
//     return (FALSE);
// }

