/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:26:39 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/06 14:13:04 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_ms *ms, int input_fd, int fds[2])
{
	t_cmd_io	io;

	init_cmd_io(&io);
	set_io_redirections(ms, ms->cmd, &io);
	redirect_fds(ms, &io, input_fd, fds);
	execute_io(ms, &io);
}

void	waiting(t_ms *ms, int pid, size_t number_of_commands)
{
	int		status;
	size_t	i;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms->last_exit_code = WEXITSTATUS(status);
	i = 0;
	while (i++ < number_of_commands - 1)
		waitpid(-1, NULL, 0);
}

void	forking(t_ms *ms, int *input_fd, int fds[2], int *pid)
{
	if (ms->cmd->next)
	{
		if (pipe(fds) == -1)
			perror("Pipe: Error parent");
	}
	*pid = fork();
	if (*pid == -1)
		perror("Fork: Error parent");
	if (*pid == 0)
		child(ms, *input_fd, fds);
	else
	{
		if (*input_fd != STDIN_FILENO)
			close(*input_fd);
		if (ms->cmd->next)
		{
			*input_fd = fds[0];
			close(fds[1]);
		}
		free_cmd_head(&ms->cmd);
	}
}

void	parent(t_ms *ms, size_t number_of_commands)
{
	int		input_fd;
	int		fds[2];
	int		pid;
	size_t	i;

	if (ms->cmd == NULL || number_of_commands <= 0)
		return ;
	input_fd = STDIN_FILENO;
	if (!ms->cmd->next && ms->cmd->argv && is_builtin_command(ms->cmd->argv[0]))
	{
		run_builtin_in_parent(ms, input_fd);
		return ;
	}
	i = 0;
	while (i++ < number_of_commands)
		forking(ms, &input_fd, fds, &pid);
	reset_redirections(ms);
	waiting(ms, pid, number_of_commands);
}

void	executer(t_ms *ms)
{
	if (ms->cmd == NULL)
		return ;
	if (!execute_heredocs(ms))
		dup2(ms->fd_stdin, STDIN_FILENO);
	else
	{
		tty_enter(1);
		parent(ms, get_number_of_commands(ms->cmd));
		tty_enter(0);
	}
	if (tty_get_flag(TTY_SIGNAL_INT))
	{
		ms->last_exit_code = 130;
		tty_set_flag(TTY_SIGNAL_INT, 0);
	}
	else if (tty_get_flag(TTY_SIGNAL_QUIT))
	{
		ms->last_exit_code = 131;
		tty_set_flag(TTY_SIGNAL_QUIT, 0);
	}
	free_cmd_io_list(&(ms->cmd_io));
	free_cmd_list(&(ms->cmd));
}
