/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:26:39 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/03 11:53:42 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_cmd_io_list(const t_cmd_io *head)
{
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

// void	set_input_io(t_ms *ms, int input_fd, t_cmd_io *cmd_io)
// {
// 	int	here_doc_fd[2];
// 	(void)ms;
// 	if (cmd_io->intype == TOKEN_INFILE)
// 	{
// 		if (dup2(cmd_io->in_fd, STDIN_FILENO) == -1)
// 			perror("dup2");
// 	}
// 	else if (cmd_io->intype == TOKEN_HERE_DOC)
// 	{
// 		if (pipe(here_doc_fd) == -1)
// 			perror("pipe");
// 		if (dup2(here_doc_fd[1], STDOUT_FILENO) == -1)
// 			perror("dup2");
// 		if (dup2(here_doc_fd[0], STDIN_FILENO) == -1)
// 			perror("dup2");
// 		write(STDOUT_FILENO, cmd_io->input, ft_strlen(cmd_io->input));
// 		close(here_doc_fd[0]);
// 		close(here_doc_fd[1]);
// 	}
// 	else
// 	{
// 		if (dup2(input_fd, STDIN_FILENO) == -1)
// 			perror("dup2");
// 		// close(input_fd);
// 	}
// }

// void	set_output_io(t_ms *ms, int fds[2], t_cmd_io *cmd_io)
// {
// 	if (cmd_io->outtype == TOKEN_REDIRECT ||
// 		cmd_io->outtype == TOKEN_REDIRECT_APPEND)
// 	{
// 		if (dup2(cmd_io->out_fd, STDOUT_FILENO) == -1)
// 			perror("dup2");
// 		close(cmd_io->out_fd);
// 	}
// 	else if (cmd_io->next)
// 	{
// 		if (dup2(fds[1], STDOUT_FILENO) == -1)
// 			perror("dup2");
// 	}
// 	else
// 	{
// 		if (dup2(ms->fd_stdout, STDOUT_FILENO) == -1)
// 			perror("dup2");
// 	}
// 	// close(fds[1]); /// <<<< MUST FIX
// }

void execute_io(t_ms *ms, t_cmd_io *io)
{
	char **new_env;
	char *path_program;

	if (!io->is_valid)
		exit_with_code(ms, 1);
	if (io->command_arr == NULL)
		exit_with_code(ms, 0);
	new_env = copy_llst_to_char_arr(&ms->env_llst, ms);
	path_program = check_program_with_path(ms, io->command_arr[0]);

	if (is_builtin_command(io->command_arr[0]))
		exit(builtin_master(ms, io->command_arr));
	else if (path_program != NULL)
	{
		if (execve(path_program, io->command_arr, new_env) == -1)
		{
			perror("execve error: ");
			exit_with_code(ms, errno);
		}
	}
	print_execution_error(io->command_arr[0], "command not found");
	ft_free_array((void **)new_env);
	if (path_program)
		free(path_program);
	// ft_putstr_fd(io->command_arr[0], 3);
	// ft_putstr_fd(": ", 3);
	// ft_putendl_fd("command not found", 3);
	exit_with_code(ms, 127);
}

// void	execute_cmd_io(t_ms *ms, t_cmd_io *cmd_io)
// {
// 	pid_t		pid;
// 	int			fds[2];
// 	int			input_fd;
// 	t_cmd_io	*cur_cmd_io;
// 	int			i;
// 	int			number_of_commands;

// 	if (cmd_io == NULL)
// 		return ;
// 	number_of_commands = 0;
// 	input_fd = STDIN_FILENO;
// 	cur_cmd_io = cmd_io;
// 	if (!cur_cmd_io->next && cur_cmd_io->command_arr)
// 	{
// 		if (is_builtin_command(cur_cmd_io->command_arr[0]))
// 		{
// 			builtin_master(ms, cmd_io->command_arr);
// 			cur_cmd_io = cur_cmd_io->next;
// 		}
// 	}
// 	while (cur_cmd_io)
// 	{
// 		if (cur_cmd_io->next)
// 		{
// 			if (pipe(fds) == -1)
// 				perror("pipe");
// 		}
// 		pid = fork();
// 		if (pid == -1)
// 			perror("fork");
// 		if (pid == 0)
// 		{
// 			set_input_io(ms, input_fd, cur_cmd_io);
// 			set_output_io(ms, fds, cur_cmd_io);
// 			execute_io(ms, cur_cmd_io);
// 		}
// 		else
// 		{
// 			if (cur_cmd_io->next)
// 			{
// 				close(input_fd);
// 				input_fd = fds[0];
// 				close(fds[1]);
// 			}
// 			else if (cur_cmd_io->next == NULL && input_fd != STDIN_FILENO)
// 				close(input_fd);
// 		}
// 		cur_cmd_io = cur_cmd_io->next;
// 		number_of_commands++;
// 	}
// 	waitpid(pid, &ms->last_exit_code, 0);
// 	i = 0;
// 	while (i++ < number_of_commands - 1)
// 		waitpid(-1, NULL, 0);
// 	dup2(ms->fd_stdin, STDIN_FILENO);
// 	// dup2(ms->fd_stdout, STDOUT_FILENO);
// 	// printf("Exit code: %s\n", ft_itoa(ms->last_exit_code >> 8));
// }

void init_cmd_io(t_cmd_io *io)
{
	io->command_arr = NULL;
	io->input = NULL;
	io->output = NULL;
	io->next = NULL;
	io->intype = -1;
	io->outtype = -1;
	io->in_fd = -1;
	io->out_fd = -1;
	io->is_valid = 1;
}

// static char	*get_heredoc_string(t_ms *ms, t_redir *redir)
// {
// 	t_redir *cur;
// 	char	*ret;

// 	if (redir == NULL)
// 		return (NULL);
// 	ret = NULL;
// 	cur = redir;
// 	while (cur)
// 	{
// 		if (cur->type == TOKEN_HERE_DOC)
// 		{
// 			if (ret)
// 				free(ret);
// 			ret = heredoc(cur->target, ms);
// 		}
// 		cur = cur->next;
// 	}
// 	return (ret);
// }

static int redir_infile(t_redir *redir, t_cmd_io *io)
{
	if (io->in_fd != -1)
		close(io->in_fd);
	// if (io->intype && io->intype == TOKEN_HERE_DOC)
	// {
	// 	free(io->input);
	// 	io->input = NULL;
	// }
	io->in_fd = open(redir->target, O_RDONLY, 0644);
	if (io->in_fd == -1)
	{
		print_file_error(redir->target);
		return (0);
	}
	io->intype = redir->type;
	io->input = redir->target;
	return (1);
}

static int redir_outfile(t_redir *redir, t_cmd_io *io)
{
	if (io->out_fd != -1)
		close(io->out_fd);
	if (redir->type == TOKEN_REDIRECT)
		io->out_fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		io->out_fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (io->out_fd == -1)
	{
		print_file_error(redir->target);
		return (0);
	}
	io->outtype = redir->type;
	io->output = redir->target;
	return (1);
}

static int redir_heredoc(t_redir *redir, t_cmd_io *io)
{
	if (io->in_fd != -1)
		close(io->in_fd);
	io->input = redir->target;
	io->intype = redir->type;
	io->in_fd = -1;
	return (1);
}

int check_redirection(t_redir *redir, t_cmd_io *io)
{
	if (redir->type == TOKEN_HERE_DOC)
		return (redir_heredoc(redir, io));
	if (redir->type == TOKEN_INFILE)
		return (redir_infile(redir, io));
	if (redir->type == TOKEN_REDIRECT || TOKEN_REDIRECT_APPEND)
		return (redir_outfile(redir, io));
}

void set_io_redirections(t_ms *ms, t_cmd *cmd, t_cmd_io *io, int fd[2])
{
	t_redir *cur;
	(void)fd;
	(void)ms;

	if (cmd == NULL)
		return;
	io->command_arr = cmd->argv;
	if (cmd->redirs == NULL)
		return;
	cur = cmd->redirs;
	while (cur)
	{
		io->is_valid = check_redirection(cur, io);
		if (!io->is_valid)
			break;
		cur = cur->next;
	}
	// if (io->is_valid)
	// {
	// if (cmd->next)
	// {
	// 	if (io->out_fd != -1)
	// 		close(io->out_fd);
	// 	io->out_fd = fd[1];
	// }
	// }
}

void reset_redirections(t_ms *ms)
{
	if (dup2(ms->fd_stdin, STDIN_FILENO) == -1)
		perror("Dup2: Error reset_redirection: stdout");
	if (dup2(ms->fd_stdout, STDOUT_FILENO) == -1)
		perror("Dup2: Error reset_redirection: stdout");
}

void close_io_fds(t_cmd_io *io)
{
	if (io == NULL)
		return;
	if (io->in_fd != -1)
	{
		close(io->in_fd);
		io->in_fd = -1;
	}
	if (io->out_fd != -1)
	{
		close(io->out_fd);
		io->out_fd = -1;
	}
}

void set_input_io(int input_fd, t_cmd_io *cmd_io)
{
	int here_doc_fd[2];

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
		// if (dup2(here_doc_fd[1], STDOUT_FILENO) == -1)
		// 	perror("Dup2: Error: set_input_io: TOKEN_HEREDOC: stdout");
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

void set_output_io(t_ms *ms, int fds[2], t_cmd_io *cmd_io)
{
	if (cmd_io->outtype == TOKEN_REDIRECT ||
		cmd_io->outtype == TOKEN_REDIRECT_APPEND)
	{
		if (dup2(cmd_io->out_fd, STDOUT_FILENO) == -1)
			perror("Dup2: Error set_output_io: TOKEN_REDIRECT");
		close(cmd_io->out_fd);
	}
	else if (ms->cmd->next)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
		{
			perror("Dup2: Error set_output_io: TOKEN_PIPE");
			close(fds[1]);
		}
	}
	else
	{
		if (dup2(ms->fd_stdout, STDOUT_FILENO) == -1)
			perror("Dup2: Error set_output_io: fd_stdout to STDOUT");
	}
}

void redirect_fds(t_ms *ms, t_cmd_io *io, int input_fd, int fd[2])
{
	set_input_io(input_fd, io);
	set_output_io(ms, fd, io);
}

void run_builtin_in_parent(t_ms *ms, int input_fd)
{
	t_cmd_io io;

	init_cmd_io(&io);
	set_io_redirections(ms, ms->cmd, &io, NULL);
	if (io.is_valid)
	{
		redirect_fds(ms, &io, input_fd, NULL);
		ms->last_exit_code = builtin_master(ms, ms->cmd->argv);
	}
	close_io_fds(&io);
	free_cmd_head(&ms->cmd);
	reset_redirections(ms);
}

void child(t_ms *ms, int input_fd, int fds[2])
{
	t_cmd_io io;

	init_cmd_io(&io);
	set_io_redirections(ms, ms->cmd, &io, fds);
	redirect_fds(ms, &io, input_fd, fds);
	execute_io(ms, &io);
}

void	waiting(t_ms *ms, int pid, size_t number_of_commands)
{
	int status;
	size_t i;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms->last_exit_code = WEXITSTATUS(status);
	i = 0;
	while (i++ < number_of_commands - 1)
		waitpid(-1, NULL, 0);
}

void parent(t_ms *ms, size_t number_of_commands)
{
	int input_fd;
	int fds[2];
	int pid;
	size_t i;

	if (ms->cmd == NULL || number_of_commands <= 0)
		return;
	input_fd = STDIN_FILENO;
	if (!ms->cmd->next && ms->cmd->argv && is_builtin_command(ms->cmd->argv[0]))
	{
		run_builtin_in_parent(ms, input_fd);
		return;
	}
	i = 0;
	while (i++ < number_of_commands)
	{
		if (ms->cmd->next)
		{
			if (pipe(fds) == -1)
				perror("Pipe: Error parent");
		}
		pid = fork();
		if (pid == -1)
			perror("Fork: Error parent");
		if (pid == 0)
			child(ms, input_fd, fds);
		else
		{
			if (input_fd != STDIN_FILENO)
				close(input_fd);
			if (ms->cmd->next)
			{
				input_fd = fds[0];
				close(fds[1]);
			}
			free_cmd_head(&ms->cmd);
		}
	}
	reset_redirections(ms);
	waiting(ms, pid, number_of_commands);
}

size_t get_number_of_commands(t_cmd *cmd)
{
	size_t i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int execute_heredocs(t_ms *ms)
{
	t_cmd	*cur_cmd;
	t_redir	*cur_redir;
	int		is_valid;
	char *tmp;

	cur_cmd = ms->cmd;
	is_valid = 1;
	while (cur_cmd)
	{
		cur_redir = cur_cmd->redirs;
		while (cur_redir)
		{
			if (cur_redir->type == TOKEN_HERE_DOC)
			{
				tmp = cur_redir->target;
				cur_redir->target = heredoc(cur_redir->target, ms, &is_valid);
				free(tmp);
				if (!is_valid)
					return (0);
			}
			cur_redir = cur_redir->next;
		}
		cur_cmd = cur_cmd->next;
	}
	return (is_valid);
}

void executer(t_ms *ms)
{
	if (ms->cmd == NULL)
		return;
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
