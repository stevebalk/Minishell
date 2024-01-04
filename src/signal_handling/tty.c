/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:49:20 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/04 13:48:30 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <stddef.h>
#include "minishell.h"

static int	g_flags;

void	tty_reset_flags(void)
{
	g_flags = 0;
}

void	tty_setup(void)
{
	struct sigaction	action;

	g_flags = 0;
	ft_bzero(&action, sizeof(action));
	action.sa_handler = signal_handler;
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	tty_enter(0);
}

void	tty_enter(int is_child)
{
	struct termios	ios;

	tty_set_flag(TTY_IS_CHILD, is_child);
	tcgetattr(STDIN_FILENO, &ios);
	if (is_child)
		ios.c_lflag |= ECHOCTL;
	else
		ios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &ios);
}

int	tty_get_flag(unsigned int index)
{
	return ((g_flags & (1 << index)) != 0);
}

void	tty_set_flag(unsigned int index, int enable)
{
	if (enable)
		g_flags |= 1 << index;
	else
		g_flags &= ~(1 << index);
}
