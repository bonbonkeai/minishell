/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:45:38 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:45:40 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int handle_redirection_token(const char *line, int i, t_token **tokens)
{
	char op[3];
	char op2[2];

	if (line[i] == line[i + 1])
	{
		op[0] = line[i];
		op[1] = line[i];
		op[2] = '\0';
		add_token(tokens, create_token(op, get_token_type(op)));
		return (2);
	}
	else
	{
		op2[0] = line[i];
		op2[1] = '\0';
		add_token(tokens, create_token(op2, get_token_type(op2)));
		return (1);
	}
}

static int handle_pipe_token(t_token **tokens)
{
	add_token(tokens, create_token("|", T_PIPE));
	return (1);
}


int get_operator_token(const char *line, int i, t_token **tokens)
{
	if (!line[i])
		return (0);
	if (line[i] == '>' || line[i] == '<')
		return (handle_redirection_token(line, i, tokens));
	if (line[i] == '|')
		return (handle_pipe_token(tokens));
	return (0);
}

// int get_operator_token(const char *line, int i, t_token **tokens)
// {
// 	char	op[3];
// 	char	op2[2];

// 	if (!line[i])
// 		return (0);
// 	if (line[i] == '>' || line[i] == '<')
// 	{
// 		if (line[i] == line[i + 1])
//         {
// 			op[0] = line[i];
//             op[1] = line[i];
//             op[2] = '\0';
// 			add_token(tokens, create_token(op, get_token_type(op)));
// 			return (2);
// 		}
// 		else
// 		{
// 			op2[0] = line[i];
//             op2[1] = '\0';
// 			add_token(tokens, create_token(op2, get_token_type(op2)));
// 			return (1);
// 		}
// 	}
// 	if (line[i] == '|')
// 	{
// 		add_token(tokens, create_token("|", T_PIPE));
// 		return (1);
// 	}
// 	return (0);
// }

int consume_word(const char *line, int i)
{
	int j = 0;
	int in_squote;
	int in_dquote;

	j = 0;
	in_squote = 0;
	in_dquote = 0;
	while (line[i + j])
	{
		if (line[i + j] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (line[i + j] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else if (!in_squote && !in_dquote && (ft_isspace(line[i + j]) || ft_strchr("<>|", line[i + j])))
			break ;
		j++;
	}
	return (j);
}

int get_word_token(const char *line, int i, t_shell *sh)
{
	int		len;
	char	*word;
	t_token	*token;

	len = consume_word(line, i);
	if (len <= 0)
		return (0);
	word = ft_substr(line, i, len);
	if (!word)
		return (len);
	if (word[0] != '\0')
	{
		token = create_token(word, T_WORD);
		if (token)
			add_token(&sh->token_list, token);
	}
	free(word);
	return (len);
}
