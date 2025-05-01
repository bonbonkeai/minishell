/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pas_sur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:05:22 by jinhuang          #+#    #+#             */
/*   Updated: 2025/05/01 16:41:55 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_hiding(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &term);
}

void	signal_showing(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag |= ~(ECHOCTL);
	tcsetattr(1, 0, &term);
}

void	signal_sigint(int sig)
{
	void (sig);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit_status_control(1);
}

void	signal_eof(void)
{
	write(STDOUT_FILENO, "\033[1A", 4);
	write(STDOUT_FILENO, "\033[12C", 5);
	write(STDOUT_FILENO, "exit\n", 5);
}
