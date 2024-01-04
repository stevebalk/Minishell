/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:45:53 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/04 14:01:52 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal_flag(int sig)
{
	if (sig == SIGINT)
		tty_set_flag(TTY_SIGNAL_INT, 1);
	else if (sig == SIGQUIT)
		tty_set_flag(TTY_SIGNAL_QUIT, 1);
}

void	signal_handler(int sig)
{
	set_signal_flag(sig);
	if (sig == SIGINT && tty_get_flag(TTY_HEREDOC))
	{
		tty_set_flag(TTY_HEREDOC, 0);
		tty_set_flag(TTY_SIGNAL_INT, 1);
		write(STDERR_FILENO, "\n", 1);
		close(STDIN_FILENO);
	}
	else if (tty_get_flag(TTY_IS_CHILD))
	{
		if (sig == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)", 19);
		write(STDERR_FILENO, "\n", 1);
	}
	else if (sig == SIGINT || sig == SIGQUIT)
	{
		if (sig == SIGINT)
		{
			if (!tty_get_flag(TTY_OMIT_LF))
				write(STDOUT_FILENO, "\n", 1);
			(rl_replace_line("", 1));
		}
		rl_on_new_line();
		rl_redisplay();
	}
}
