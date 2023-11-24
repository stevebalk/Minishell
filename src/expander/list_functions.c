/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:47:25 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/24 17:28:35 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create an expand node and initalize it */
t_expand	*create_expand_node(t_ms *ms)
{
	t_expand	*node;

	node = malloc(1 * sizeof(t_expand));
	check_if_malloc_failed((void *)node, ms);
	node->next = NULL;
	node->str = NULL;
	return (node);
}

/* Appends to the ms.exp linked list or creates the
first node if there isn't one */
t_expand	*append_chunk(t_ms *ms)
{
	t_expand	*cur;

	if (ms->exp == NULL)
	{
		ms->exp = create_expand_node(ms);
		return (ms->exp);
	}
	cur = ms->exp;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = create_expand_node(ms);
	return (cur->next);
}
