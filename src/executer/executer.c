/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:26:39 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/19 16:52:25 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_cmd_io_list(const t_cmd_io *head) {
	const t_cmd_io *current = head;

	while (current != NULL)
	{
		printf("Input: %s\n", current->input ? current->input : "NULL");
		printf("Input Type: %d\n", current->intype);
		printf("Input File Descriptor: %d\n", current->in_fd);
		printf("Output: %s\n", current->output ? current->output : "NULL");
		printf("Output Type: %d\n", current->outtype);
		printf("Output File Descriptor: %d\n", current->out_fd);
		printf("Command Array:\n");

		if (current->command_arr != NULL)
		{
			for (int i = 0; current->command_arr[i] != NULL; ++i)
			{
				printf("  %s\n", current->command_arr[i]);
			}
		}
		else
		{
			printf("  NULL\n");
		}

		printf("Is Valid: %d\n", current->is_valid);
		printf("Next: %p\n", (void *)current->next);

		current = current->next;
		ft_putendl_fd("", 1);
	}
}

void	set_input_io(t_ms *ms, int input_fd, t_cmd_io *cmd_io)
{
	int	here_doc_fd[2];
	(void)ms;
	if (cmd_io->intype == TOKEN_INFILE)
	{
		if (dup2(cmd_io->in_fd, STDIN_FILENO) == -1)
			perror("dup2");
	}
	else if (cmd_io->intype == TOKEN_HERE_DOC)
	{
		if (pipe(here_doc_fd) == -1)
			perror("pipe");
		if (dup2(here_doc_fd[1], STDOUT_FILENO) == -1)
			perror("dup2");
		if (dup2(here_doc_fd[0], STDIN_FILENO) == -1)
			perror("dup2");
		write(STDOUT_FILENO, cmd_io->input, ft_strlen(cmd_io->input));
		close(here_doc_fd[0]);
		close(here_doc_fd[1]);
	}
	else
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			perror("dup2");
		close(input_fd);
	}
}

void	set_output_io(t_ms *ms, int fds[2], t_cmd_io *cmd_io)
{
	if (cmd_io->outtype == TOKEN_REDIRECT ||
		cmd_io->outtype == TOKEN_REDIRECT_APPEND)
	{
		if (dup2(cmd_io->out_fd, STDOUT_FILENO) == -1)
			perror("dup2");
		close(cmd_io->out_fd);
	}
	else if (cmd_io->next)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			perror("dup2");
	}
	else
	{
		if (dup2(ms->fd_stdout, STDOUT_FILENO) == -1)
			perror("dup2");
	}
	close(fds[1]);
}

void	execute_io(t_cmd_io *cmd_io)
{
	execvp(cmd_io->command_arr[0], cmd_io->command_arr); // CHANGE TO THE RIGHT COMMAND!!!!
	perror(cmd_io->command_arr[0]);
	perror("command does not exist");
	exit(127);
}

void	execute_cmd_io(t_ms *ms, t_cmd_io *cmd_io)
{
	pid_t		pid;
	int			fds[2];
	int			input_fd;
	t_cmd_io	*cur_cmd_io;
	int			i;
	int			number_of_commands;

	if (cmd_io == NULL)
		return ;
	number_of_commands = 0;
	input_fd = ms->fd_stdin;
	cur_cmd_io = cmd_io;
	while (cur_cmd_io)
	{
		if (cur_cmd_io->next)
		{
			if (pipe(fds) == -1)
				perror("pipe");
		}
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			set_input_io(ms, input_fd, cur_cmd_io);
			set_output_io(ms, fds, cur_cmd_io);
			execute_io(cur_cmd_io);
		}
		else
		{
			if (cur_cmd_io->next)
			{
				if (input_fd != STDIN_FILENO)
					close(input_fd);
				input_fd = fds[0];
				close(fds[1]);
			}
			else if (cur_cmd_io->next == NULL && input_fd != STDIN_FILENO)
				close(input_fd);
		}
		cur_cmd_io = cur_cmd_io->next;
		number_of_commands++;
	}
	waitpid(pid, &ms->last_exit_code, 0);
	i = 0;
	while (i++ < number_of_commands - 1)
		waitpid(-1, NULL, 0);
	printf("Exit code: %s\n", ft_itoa(ms->last_exit_code >> 8));
}

void	executer(t_ms *ms)
{
	if (ms->cmd == NULL)
		return ;
	create_cmd_io_list(ms);
	// print_cmd_io_list(ms->cmd_io);
	execute_cmd_io(ms, ms->cmd_io);
	free_cmd_io_list(&(ms->cmd_io));
	free_cmd_list(&(ms->cmd));
}
