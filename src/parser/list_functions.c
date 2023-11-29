/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:47:50 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/28 17:18:52 by sbalk            ###   ########.fr       */
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
