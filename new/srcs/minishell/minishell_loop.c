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

static char *safe_prompt(t_shell *shell)
{
    char *prompt;
    
    prompt = build_prompt(shell);
    if (!prompt)
        prompt = ft_strdup("minishell$ ");
    return (prompt);
}

// void minishell_loop(t_shell *shell)
// {
// 	char *line;
//     char *prompt;

// 	while (1)
// 	{
//         prompt = safe_prompt(shell);
//         if (!prompt)
//         {
//             write(2, "Error: failed to allocate prompt\n", 33);
//             break ;
//         }
//         line = readline(prompt);
//         free(prompt);
// 		if (!line)
//         {
//             write(1, "exit\n", 5);     
//             break ;
//         }
// 		if (line[0])
// 			add_history(line);
//         if (ft_strncmp(line, "exit", 4) == 0 && (line[4] == '\0' || ft_isspace(line[4])))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		process_input(shell, line);
// 		free(line);
// 	}
// }

static char *generate_prompt(t_shell *sh)
{
	char *prompt;

	prompt = safe_prompt(sh);
	if (!prompt)
		write(2, "Error: failed to allocate prompt\n", 33);
	return (prompt);
}

static bool handle_input_line(t_shell *shell, char *line)
{
	if (!line)
	{
		write(1, "exit\n", 5);
		return (false);
	}
	if (line[0])
		add_history(line);
	if (ft_strncmp(line, "exit", 4) == 0 && (line[4] == '\0' || ft_isspace(line[4])))
	{
		free(line);
		return (false);
	}
	process_input(shell, line);
	free(line);
	return (true);
}

void minishell_loop(t_shell *shell)
{
	char *line;
	char *prompt;

	while (1)
	{
		prompt = generate_prompt(shell);
		if (!prompt)
			break ;
		line = readline(prompt);
		free(prompt);
		if (!handle_input_line(shell, line))
			break ;
	}
}
