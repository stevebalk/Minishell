/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:36:30 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/12 16:17:15 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

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
	}
}

/* Creates initilized cmd_io if successful */
t_cmd_io	*create_cmd_io_node(t_ms *ms)
{
	t_cmd_io	*io;

	io = ft_calloc(1, sizeof(t_cmd_io));
	check_if_malloc_failed((void *)io, ms);
	io->intype = -1;
	io->outtype = -1;
	return (io);
}

/* Creates a new empty cmd_io and appends it to
the linked list. If there is no head token it
will assignes the cmd_io as head */
t_cmd_io	*cmd_io_append_node(t_ms *ms)
{
	t_cmd_io	*cur;

	if (ms->cmd_io == NULL)
	{
		ms->cmd_io = create_cmd_io_node(ms);
		return (ms->cmd_io);
	}
	else
	{
		cur = ms->cmd_io;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = create_cmd_io_node(ms);
	}
	return (cur->next);
}

void	print_file_error(t_ms *ms, char *msg)
{
	(void) ms;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(":", STDERR_FILENO);
	perror();
}


static int	redir_to_io(t_ms *ms, t_redir *redir, t_cmd_io *io)
{
	if (redir->type == TOKEN_INFILE)
	{
		if (io->in_fd != -1)
			close(io->in_fd);
		if (io->intype && io->intype == TOKEN_HERE_DOC)
			free(io->input);
		io->in_fd = open(redir->target, O_RDONLY, 0644);
		if (fd == -1)
		{
			print_file_error(ms, redir->target);
			return (0);
		}
		io->intype = redir->type;
		io->input = redir->target;
	}
	if (redir->type == TOKEN_REDIRECT || redir->type == TOKEN_REDIRECT_APPEND)
	{
		if (io->out_fd != -1)
			close(io->out_fd);
		io->out_fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			print_file_error(ms, redir->target);
			return (0);
		}
		io->output = redir->target;
	}
	if (redir->type == TOKEN_HERE_DOC)
	{
		if (io->in_fd != -1)
			close(io->in_fd);
		if (io->intype && io->intype == TOKEN_HERE_DOC)
			free(io->input);
		io->input = heredoc(redir->target, ms);
		io->intype = redir->type;
		io->in_fd = -1;
	}
	return (1);
}

void	fill_cmd_io_node(t_ms *ms, t_redir *redir, t_cmd_io *io)
{
	t_redir	*cur;

	if (redir == NULL)
		return (1);
	cur = redir;
	while (cur)
	{
		io->is_valid = redir_to_io(ms, cur, io)
		if (io->is_valid)
			cur = cur->next;
		else
			break;
	}
}

void	create_cmd_io(t_ms *ms)
{
	t_cmd		*cmd_cur;
	t_cmd_io	*cmd_io_cur;

	cmd_cur = ms->cmd;
	while (cmd_cur)
	{
		cmd_io_cur = cmd_io_append_node(ms);
		cmd_io_cur->command_arr = cmd_cur->argv;
		fill_cmd_io_node(cmd_cur->redirs, cmd_io_cur);
		cmd_cur = cmd_cur->next;
	}
}

void	executer(t_ms *ms)
{
	if (ms->cmd == NULL)
		return ;
	create_cmd_io(ms);
	print_cmd_io_list(ms->cmd_io);
}
