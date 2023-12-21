/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_to_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:19:38 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/21 17:36:06 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_infile_to_io(t_redir *redir, t_cmd_io *io)
{
	if (io->in_fd != -1)
		close(io->in_fd);
	if (io->intype && io->intype == TOKEN_HERE_DOC)
	{
		free(io->input);
		io->input = NULL;
	}
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

static int	redir_outfile_to_io(t_redir *redir, t_cmd_io *io)
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

static void	redir_heredoc_to_io(t_redir *redir, t_cmd_io *io, char *hd_str)
{
	if (io->in_fd != -1)
		close(io->in_fd);
	io->input = hd_str;
	io->intype = redir->type;
	io->in_fd = -1;
}


int	redir_to_io(t_redir *redir, t_cmd_io *io, char *heredoc_str)
{
	int	ret;

	ret = 1;
	if (redir->type == TOKEN_INFILE)
		ret = redir_infile_to_io(redir, io);
	if (redir->type == TOKEN_REDIRECT || redir->type == TOKEN_REDIRECT_APPEND)
		ret = redir_outfile_to_io(redir, io);
	if (redir->type == TOKEN_HERE_DOC)
		redir_heredoc_to_io(redir, io, heredoc_str);
	return (ret);
}
