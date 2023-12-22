/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 12:48:42 by jonas             #+#    #+#             */
/*   Updated: 2023/12/22 13:37:24 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	g_flags = 0;

static void	signal_handler(int number)
{
	if (number == SIGINT && tty_get_flag(TTY_HEREDOC))
	{
		tty_set_flag(TTY_HEREDOC, 0);
		write(STDERR_FILENO, "\n", 1);
		close(STDIN_FILENO);
		return ;
	}
	if (tty_get_flag(TTY_IS_CHILD))
	{
		if (number == SIGQUIT)
			write(STDERR_FILENO, "Quit\n", 5);
		else
			write(STDERR_FILENO, "\n", 1);
		return ;
	}
	if (number == SIGINT || number == SIGQUIT)
	{
		if (number == SIGINT)
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
	action.sa_flags = 0;
	action.sa_mask = 0;
	//ms_zero(&action, sizeof(action));
	action.sa_handler = signal_handler;
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);

	// kann evtl auch mit sigaddset udn sigemptyset gelöst werden
	tty_enter(0);
}

void	tty_enter(int is_child)
{
	struct termios	ios;

	tty_set_flag(TTY_IS_CHILD, is_child);
	tcgetattr(STDIN_FILENO, &ios);				// get the behaviour of the terminal
	if (is_child)
		ios.c_lflag |= ECHOCTL;					// enables (set bit) the echo of CTL + character
	else
		ios.c_lflag &= ~ECHOCTL;				// disables (unset bit) the echo of CTL + character
	tcsetattr(STDIN_FILENO, TCSANOW, &ios);		// set the behaviour of the terminal
}

// return 1 if index is settet 0 if not
int	tty_get_flag(unsigned int index)
{
	return ((g_flags & (1 << index)) != 0);
}

// set flags bit nr index to 1 (enable 1) or to 0 (enable 0)
void	tty_set_flag(unsigned int index, int enable)
{
	if (enable)
		g_flags |= 1 << index;		
	else
		g_flags &= ~(1 << index);   
}