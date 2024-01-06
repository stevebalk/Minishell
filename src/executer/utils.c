/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:42:54 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/06 14:00:19 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd_io(t_cmd_io *io)
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

void	close_io_fds(t_cmd_io *io)
{
	if (io == NULL)
		return ;
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

int	is_regular_file(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

size_t	get_number_of_commands(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}
