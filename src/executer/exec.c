/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:36:30 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/12 13:33:35 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

void	get_redirections(t_ms *ms, t_cmd_io *io)
{
	t_redir	*cur;

	cur = ms->cmd->redirs;
	io = {NULL, NULL, -1, NULL, NULL, -1};
	while (cur)
	{
		if (cur->type == TOKEN_HERE_DOC)
		{
			if (redirs->heredoc_string)
				free(redirs->heredoc_string);
			redirs->heredoc_string = heredoc(cur->target, ms);
		}
	}
}

void	execute_cmd_block(t_ms *ms)
{
	t_io	cur;

	while (ms->cmd->redirs)
	{

		if ()
	}
}

void	executer(t_ms *ms)
{
	if (ms->cmd == NULL)
		return ;
	while (ms->cmd)
		execute_cmd_block(ms);

}