/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:28:20 by jdu               #+#    #+#             */
/*   Updated: 2025/07/11 21:08:26 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_and_exit(t_shell *sh, int error_status)
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
	if (g_signal == SIGINT)
	{
		sh->status = 130;
	}
	else
		sh->status = error_status;
}

static char	*safe_prompt(t_shell *shell)
{
	char	*prompt;

	prompt = build_prompt(shell);
	if (!prompt)
		prompt = ft_strdup("minishell$ ");
	return (prompt);
}

static bool	handle_input_line(t_shell *shell, char *line)
{
	if (!line)
	{
		write(1, "exit\n", 5);
		clear_history();
		return (false);
	}
	if (line[0])
		add_history(line);
	if (g_signal == SIGINT)
		shell->status = 130;
	process_input(shell, line);
	free(line);
	g_signal = 0;
	rl_done = 0;
	return (true);
}

void	minishell_loop(t_shell *shell)
{
	char	*line;
	char	*prompt;

	rl_bind_key('\t', rl_insert);
	while (1)
	{
		signal_inloop();
		if (g_signal != SIGINT)
			prompt = safe_prompt(shell);
		if (!prompt)
		{
			write(2, "Error: failed to allocate prompt\n", 33);
			break ;
		}
		if (!prompt)
			break ;
		line = readline(prompt);
		free(prompt);
		if (!handle_input_line(shell, line))
			break ;
	}
}

// static char	*read_line_opt(char *line, char *prompt)
// {
// 	if (isatty(STDIN_FILENO))
// 		line = readline(prompt);
// 	else
// 		line = get_next_line(fileno(stdin));
// 	return (line);
// }

// void	minishell_loop(t_shell *shell)
// {
// 	char	*line;
// 	char	*prompt;

// 	rl_bind_key('\t', rl_insert);
// 	while (1)
// 	{
// 		signal_inloop();
// 		if (g_signal != SIGINT)
// 			prompt = safe_prompt(shell);
// 		if (!prompt)
// 		{
// 			write(2, "Error: failed to allocate prompt\n", 33);
// 			break ;
// 		}
// 		line = read_line_opt(line, prompt);
// 		if (line == NULL)
// 		{
// 			free(prompt);
// 			if (isatty(STDERR_FILENO))
// 				ft_putendl_fd("exit", STDERR_FILENO);
// 			break ;
// 		}
// 		free(prompt);
// 		if (!handle_input_line(shell, line))
// 			break ;
// 	}
// }
