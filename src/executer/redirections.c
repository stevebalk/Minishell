/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:48:40 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/06 16:46:09 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_redirections(t_ms *ms)
{
	if (dup2(ms->fd_stdin, STDIN_FILENO) == -1)
		perror("Dup2: Error reset_redirection: stdout");
	if (dup2(ms->fd_stdout, STDOUT_FILENO) == -1)
		perror("Dup2: Error reset_redirection: stdout");
}

void	set_input_io(int input_fd, t_cmd_io *cmd_io)
{
	int		here_doc_fd[2];

	if (cmd_io->intype == TOKEN_INFILE)
	{
		if (dup2(cmd_io->in_fd, STDIN_FILENO) == -1)
		{
			perror("Dup2: Error set_input_io: TOKEN_INFILE");
			close(cmd_io->in_fd);
		}
	}
	else if (cmd_io->intype == TOKEN_HERE_DOC)
	{
		if (pipe(here_doc_fd) == -1)
			perror("Pipe: Error: set_input_io: TOKEN_HEREDOC");
		if (dup2(here_doc_fd[0], STDIN_FILENO) == -1)
			perror("Dup2: Error: set_input_io: TOKEN_HEREDOC: stdin");
		write(here_doc_fd[1], cmd_io->input, ft_strlen(cmd_io->input));
		close(here_doc_fd[0]);
		close(here_doc_fd[1]);
	}
	else
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			perror("Dup2: Error set_input_io: input_fd to STDIN");
	}
}

void	set_output_io(t_ms *ms, int fds[2], t_cmd_io *cmd_io)
{
	if (cmd_io->outtype == TOKEN_REDIRECT
		|| cmd_io->outtype == TOKEN_REDIRECT_APPEND)
	{
		if (dup2(cmd_io->out_fd, STDOUT_FILENO) == -1)
			perror("Dup2: Error set_output_io: TOKEN_REDIRECT");
		close(cmd_io->out_fd);
	}
	else if (ms->cmd->next)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			perror("Dup2: Error set_output_io: TOKEN_PIPE");
	}
	else
	{
		if (dup2(ms->fd_stdout, STDOUT_FILENO) == -1)
			perror("Dup2: Error set_output_io: fd_stdout to STDOUT");
	}
}

void	set_io_redirections(t_ms *ms, t_cmd *cmd, t_cmd_io *io)
{
	t_redir	*cur;

	if (cmd == NULL)
		return ;
	io->command_arr = cmd->argv;
	if (cmd->redirs == NULL)
		return ;
	cur = cmd->redirs;
	while (cur)
	{
		io->is_valid = check_redirection(cur, io);
		if (!io->is_valid)
		{
			if (io->in_fd != -1)
				close(io->in_fd);
			if (io->out_fd != -1)
				close(io->out_fd);
			exit_with_code(ms, 1);
		}
		cur = cur->next;
	}
}

void	redirect_fds(t_ms *ms, t_cmd_io *io, int input_fd, int fds[2])
{
	set_input_io(input_fd, io);
	set_output_io(ms, fds, io);
	if (ms->cmd->next != NULL)
	{
		close(fds[1]);
		close(fds[0]);
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
}
