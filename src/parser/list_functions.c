/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:47:50 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/29 17:12:25 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create a cmd node and initalize it */
t_cmd	*create_cmd_node(t_ms *ms)
{
	t_cmd	*node;

	node = malloc(1 * sizeof(t_cmd));
	check_if_malloc_failed((void *)node, ms);
	node->next = NULL;
	node->argv = NULL;
	node->redirs = NULL;
	return (node);
}

/* Appends to the ms.cmd linked list or creates the
first node if there isn't one */
t_cmd	*append_cmd_node(t_ms *ms)
{
	t_cmd	*cur;

	if (ms->cmd == NULL)
	{
		ms->cmd = create_cmd_node(ms);
		return (ms->cmd);
	}
	cur = ms->cmd;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = create_cmd_node(ms);
	return (cur->next);
}

void	free_cmd_list_exept_here_doc(t_cmd *cmd)
{
	t_cmd	*cmd_next;
	t_redir	*redir_next;
	t_redir	*new_list;

	new_list = NULL;
	while (cmd)
	{
		cmd_next = cmd->next;
		ft_free_array((void **) cmd->argv);
		while (cmd->redirs)
		{
			redir_next = cmd->redirs;
			if (cmd->redirs->type != TOKEN_HERE_DOC)
			{
				free_redir_node(cmd->redirs);
				cmd->redirs = redir_next;
			}
			else
			{}
		}
	}
}
