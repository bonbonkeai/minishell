/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:29:10 by jdu               #+#    #+#             */
/*   Updated: 2025/07/09 14:21:36 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	lexer_input(t_shell *sh, char *input)
{
	sh->trimmed_prompt = ft_strtrim(input, " \t\n");
	if (!sh->trimmed_prompt || sh->trimmed_prompt[0] == '\0')
	{
		free(sh->trimmed_prompt);
		sh->trimmed_prompt = NULL;
		return (false);
	}
	if (g_signal == SIGINT || !lexer(sh))
	{
		cleanup_and_exit(sh, 2);
		return (false);
	}
	return (true);
}

static bool	tokenize_and_parse(t_shell *sh)
{
	if (sh->token_list)
	{
		free_tokens(sh->token_list);
		sh->token_list = NULL;
	}
	tokenize_prompt(sh, sh->trimmed_prompt);
	if (g_signal == SIGINT || !sh->token_list \
		|| check_token_syntax(sh->token_list))
	{
		cleanup_and_exit(sh, 2);
		return (false);
	}
	return (true);
}

static bool	expand_and_check(t_shell *sh, t_suffix_type *illegal_type, \
				char *error_char)
{
	int	status;

	if (g_signal == SIGINT || !expand_all(sh, illegal_type, error_char))
	{
		has_illegal_expansion(*illegal_type, *error_char);
		if (*illegal_type == SUFFIX_OK && *error_char == 0)
			status = 0;
		else
			status = 2;
		cleanup_and_exit(sh, status);
		return (false);
	}
	return (true);
}

// void	print_cmd_list(t_cmd *cmd_list)
// {
// 	t_cmd *curr = cmd_list;
// 	int i;
// 	while (curr)
// 	{
// 		printf("cmd: ");
// 		if (curr->cmd)
// 			printf("%s\n", curr->cmd);
// 		else
// 			printf("(null)\n");

// 		if (curr->args)
// 		{
// 			i = 0;
// 			while (curr->args[i])
// 			{
// 				printf("  args[%d]: %s\n", i, curr->args[i]);
// 				i++;
// 			}
// 		}
// 		else
// 			printf("  args: (null)\n");
// 		printf("  redirs: ");
// 		if (curr->red)
// 		{
// 			for (i = 0; curr->red[i]; i++)
// 				printf("%s ", curr->red[i]);
// 			printf("\n");
// 		}
// 		else
// 			printf("(none)\n");
// 		curr = curr->next;
// 	}
// }

void	remove_empty_args(t_cmd *cmd_list)
{
	t_cmd	*curr;
	int		i;

	curr = cmd_list;
	while (curr)
	{
		if (curr->args && curr->args[0] && curr->args[0][0] == '\0')
		{
			free(curr->args[0]);
			i = 0;
			while (curr->args[i + 1])
			{
				curr->args[i] = curr->args[i + 1];
				i++;
			}
			curr->args[i] = NULL;
			if (curr->cmd)
				free(curr->cmd);
			curr->cmd = ft_strdup(curr->args[0]);
		}
		curr = curr->next;
	}
}

void	process_input(t_shell *sh, char *input)
{
	t_suffix_type	illegal_type;
	char			error_char;
	t_cmd			*cmd;

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
	remove_empty_args(sh->cmd);
	sh->curr_cmd = sh->cmd;
	if (sh->cmd && g_signal != SIGINT)
		sh->status = executor(sh);
	if (g_signal == SIGINT)
		sh->status = 130;
	cleanup_and_exit(sh, sh->status);
}
