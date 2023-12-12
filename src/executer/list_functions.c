/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:17:21 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/12 18:18:19 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Creates initilized cmd_io if successful */
t_cmd_io	*create_cmd_io_node(t_ms *ms)
{
	t_cmd_io	*io;

	io = ft_calloc(1, sizeof(t_cmd_io));
	check_if_malloc_failed((void *)io, ms);
	io->intype = -1;
	io->outtype = -1;
	io->in_fd = -1;
	io->out_fd = -1;
	io->is_valid = 1;
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
