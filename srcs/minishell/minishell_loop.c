/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:28:20 by jdu               #+#    #+#             */
/*   Updated: 2025/07/01 20:28:10 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (false);
	}
	if (line[0])
		add_history(line);
	if (ft_strncmp(line, "exit", 4) == 0 && \
		(line[4] == '\0' || ft_isspace(line[4])))
	{
		free(line);
		return (false);
	}
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
		signal_handle();
		signal_showing();
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
