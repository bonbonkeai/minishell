/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:36:27 by jdu               #+#    #+#             */
/*   Updated: 2025/07/01 19:36:38 by jdu              ###   ########.fr       */
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
