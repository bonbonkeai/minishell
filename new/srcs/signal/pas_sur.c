/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pas_sur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:05:22 by jinhuang          #+#    #+#             */
/*   Updated: 2025/05/02 16:46:19 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_hiding(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, TCSANOW, &term);
}

void	signal_showing(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	 term.c_lflag |= ECHOCTL;
	tcsetattr(1, 0, &term);
}

void	signal_sigint(int sig)
{
	(void) sig;
	//write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	//rl_redisplay();
	//exit_status_control(1);
}

void	signal_eof(void)
{
	write(STDOUT_FILENO, "\033[1A", 4);
	write(STDOUT_FILENO, "\033[12C", 5);
	write(STDOUT_FILENO, "exit\n", 5);
}

void	signal_handle(void)
{
	signal_hiding();
	signal(SIGINT, signal_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handle_fork(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_heredoc(void)
{
	signal(SIGINT, sigint_hl_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_hl_heredoc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit (1);
}

// void	check_fork_signal(int statloc)
// {
// 	if ((statloc & 255) != 0)
// 	{
// 		if ((statloc & 127) == 2)
// 			write(STDERR_FILENO, "\n", 1);
// 		else if ((statloc & 127) == 3)
// 			write(STDERR_FILENO, "Quit: 3\n", 8);
// 	}
// }