/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_io.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:23:24 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/12 18:25:26 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_cmd_io_node(t_ms *ms, t_redir *redir, t_cmd_io *io)
{
	t_redir	*cur;

	if (redir == NULL)
		return ;
	cur = redir;
	while (cur)
	{
		io->is_valid = redir_to_io(ms, cur, io);
		if (io->is_valid)
			cur = cur->next;
		else
			break;
	}
}

void	create_cmd_io_list(t_ms *ms)
{
	t_cmd		*cmd_cur;
	t_cmd_io	*cmd_io_cur;

	cmd_cur = ms->cmd;
	while (cmd_cur)
	{
		cmd_io_cur = cmd_io_append_node(ms);
		cmd_io_cur->command_arr = cmd_cur->argv;
		fill_cmd_io_node(ms, cmd_cur->redirs, cmd_io_cur);
		cmd_cur = cmd_cur->next;
	}
}
