/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:41:40 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/06 16:33:53 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_infile(t_redir *redir, t_cmd_io *io)
{
	if (io->in_fd != -1)
	{
		io->in_fd = -1;
		close(io->in_fd);
	}
	if (redir->target == NULL)
		return (0);
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

static int	redir_outfile(t_redir *redir, t_cmd_io *io)
{
	if (io->out_fd != -1)
	{
		io->out_fd = -1;
		close(io->out_fd);
	}
	if (redir->target == NULL)
		return (0);
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

static int	redir_heredoc(t_redir *redir, t_cmd_io *io)
{
	if (io->in_fd != -1)
		close(io->in_fd);
	io->input = redir->target;
	io->intype = redir->type;
	io->in_fd = -1;
	return (1);
}

int	check_redirection(t_redir *redir, t_cmd_io *io)
{
	if (redir->type == TOKEN_HERE_DOC)
		return (redir_heredoc(redir, io));
	if (redir->type == TOKEN_INFILE)
		return (redir_infile(redir, io));
	if (redir->type == TOKEN_REDIRECT || redir->type == TOKEN_REDIRECT_APPEND)
		return (redir_outfile(redir, io));
	return (0);
}
