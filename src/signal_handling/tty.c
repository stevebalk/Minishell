/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:49:20 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/02 16:14:49 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <stddef.h>
#include "minishell.h"

static int	g_flags;

// static void	signal_handler(int sig)
// {
// 	if (sig == SIGINT && tty_get_flag(TTY_HEREDOC))
// 	{
// 		tty_set_flag(TTY_HEREDOC, 0);
// 		write(STDERR_FILENO, "\n", 1);
// 		close(STDIN_FILENO);
// 		return ;
// 	}
// 	if (tty_get_flag(TTY_IS_CHILD))
// 	{
// 		if (sig == SIGQUIT)
// 			write(STDERR_FILENO, "Quit\n", 5);
// 		else
// 			write(STDERR_FILENO, "\n", 1);
// 		return ;
// 	}
// 	if (sig == SIGINT || sig == SIGQUIT)
// 	{
// 		if (sig == SIGINT)
// 		{
// 			if (!tty_get_flag(TTY_OMIT_LF))
// 				write(STDOUT_FILENO, "\n", 1);
// 			(rl_replace_line("", 1), rl_on_new_line());
// 		}
// 		rl_redisplay();
// 	}
// }

void	set_signal_flag(int sig)
{
	if (sig == SIGINT)
		tty_set_flag(TTY_SIGNAL_INT, 1);
	else if (sig == SIGQUIT)
		tty_set_flag(TTY_SIGNAL_QUIT, 1);
}

static void	signal_handler(int sig)
{
	set_signal_flag(sig);
	if (sig == SIGINT && tty_get_flag(TTY_HEREDOC))
	{
		tty_set_flag(TTY_HEREDOC, 0);
		tty_set_flag(TTY_SIGNAL_INT, 1);
		write(STDERR_FILENO, "\n", 1);
		close(STDIN_FILENO);
		return ;
	}
	if (tty_get_flag(TTY_IS_CHILD))
	{
		if (sig == SIGQUIT)
			write(STDERR_FILENO, "Quit", 4);
		write(STDERR_FILENO, "\n", 1);
		return ;
	}
	if (sig == SIGINT || sig == SIGQUIT)
	{
		if (sig == SIGINT)
		{
			if (!tty_get_flag(TTY_OMIT_LF))
				write(STDOUT_FILENO, "\n", 1);
			(rl_replace_line("", 1), rl_on_new_line());
		}
		rl_redisplay();
	}
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
