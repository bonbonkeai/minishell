/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:13:28 by jdu               #+#    #+#             */
/*   Updated: 2025/07/01 20:45:54 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_too_many_redir(const char *input, int i)
{
	if (is_too_many_char(input, i, '>'))
		return (syntax_error_pipex(">>"), TRUE);
	if (is_too_many_char(input, i, '<'))
		return (syntax_error_pipex("<<"), TRUE);
	return (FALSE);
}

int	check_spacing_errors(const char *input, int i)
{
	if (input[i] == '>' && input[i + 1] == '>' && \
		next_non_space(input, i + 1) == '>')
		return (syntax_error_pipex(">>"), TRUE);
	else if (input[i] == '<' && input[i + 1] == '<' && \
		next_non_space(input, i + 1) == '<')
		return (syntax_error_pipex("<<"), TRUE);
	if (input[i] == '>' && input[i + 1] != '>' && \
		next_non_space(input, i) == '>')
		return (syntax_error_pipex(">"), TRUE);
	if (input[i] == '<' && input[i + 1] != '<' && \
		next_non_space(input, i) == '<')
		return (syntax_error_pipex("<"), TRUE);
	if ((input[i] == '>' || input[i] == '<') && \
		next_non_space(input, i) == '<' && \
		!(input[i] == '<' && input[i + 1] == '<'))
		return (syntax_error_pipex("<"), TRUE);
	return (FALSE);
}

int	check_double_pipe(const char *input, int i)
{
	if (input[i] == '|' && input[i + 1] == '|')
		return (syntax_error_pipex("||"), TRUE);
	if (input[i] == '|' && next_non_space(input, i) == '|')
		return (syntax_error_pipex("|"), TRUE);
	return (FALSE);
}

int	check_mixed_combos(const char *input, int i)
{
	if (input[i] == '>' && input[i + 1] == '<')
		return (syntax_error_pipex("<"), TRUE);
	if (input[i] == '<' && input[i + 1] == '>')
		return (syntax_error_newline(), TRUE);
	return (FALSE);
}

int	is_invalid_operator(const char *input, int i)
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
