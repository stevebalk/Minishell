/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:26:39 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/18 16:39:46 by jopeters         ###   ########.fr       */
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

// void	child1(t_ms *ms, t_cmd_io *cmd_io, int fd[2])
// {
// 	close(fd[0]);
// }

// void	child2(t_ms *ms)
// {
	
// 	exit(0);
// }

// void	execution(t_ms *ms)
// {
// 	int			fd[2];
// 	pid_t		pid;
// 	int			stat_loc;
// 	t_cmd_io	*cur_cmd_io;

// 	stat_loc = 0;
// 	cur_cmd_io = ms->cmd_io;
// 	if (cur_cmd_io == NULL)
// 		return ;
// 	while (cur_cmd_io->next)
// 	{
// 		if (pipe(&fd) == -1);
// 			ERROR_HANDLING;
// 		pid = fork();
// 		if (pid == -1)
// 			ERROR_HANDLING;
// 		if (pid == 0)
// 		{
// 			child1(ms, cur_cmd_io);
// 		}
// 		else if (pid > 0)
// 		{
// 			wait(NULL);
// 			pid = fork();
// 		}
// 		if (pid == 0)
// 		{
// 			child2(ms, cur_cmd_io->next);
// 			wait(NULL);
// 		}
// 		cur_cmd_io = cur_cmd_io->next;
// 	}
// 	waitpid(pid, &stat_loc, NULL);
// }

void	set_input_io(t_ms *ms, int input_fd, t_cmd_io *cmd_io)
{
	if (cmd_io->intype == TOKEN_INFILE)
	{
		if (dup2(cmd_io->in_fd, STDIN_FILENO) == -1)
			perror("dup2");
		
	}
	else if (cmd_io->intype == TOKEN_HERE_DOC)
	{
		if (dup2(ms->fd_stdin, STDIN_FILENO) == -1)
			perror("dup2");
	}
	else
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			perror("dup2");
		close(input_fd);
	}
	// else if (cmd_io->next)
	// {
	// 	if (dup2(input_fd, STDIN_FILENO) == -1)
	// 		perror("dup2");
	// }
	// else
	// 	if (dup2(ms->fd_stdin, STDIN_FILENO) == -1)
	// 		perror("dup2");
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

void	execute_io(t_ms *ms, t_cmd_io *cmd_io)
{
	if (is_builtin_command(cmd_io->command_arr[0]))
		builtin_master(ms, cmd_io->command_arr);
	else
		execvp(cmd_io->command_arr[0], cmd_io->command_arr); // CHANGE TO THE RIGHT COMMAND!!!!
	perror("command does not exist");
	exit(errno);
}

void	execute_cmd_io(t_ms *ms, t_cmd_io *cmd_io)
{
	pid_t		pid;
	int			fds[2];
	int			input_fd;
	t_cmd_io	*cur_cmd_io;

	if (cmd_io == NULL)
		return ;
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
			execute_io(ms, cur_cmd_io);
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
		waitpid(pid, NULL, 0);
		cur_cmd_io = cur_cmd_io->next;
	}
	// for (int i = 0; i < 3; i++)
	// {
	// }
}

// void	execution(t_ms *ms)
// {
// 	t_cmd_io	*cur_cmd_io;

// 	cur_cmd_io = ms->cmd_io;
// 	if (ms->cmd_io == NULL)
// 		return ;
// 	while (cur_cmd_io)
// 	{
		
// 	}
// }

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
