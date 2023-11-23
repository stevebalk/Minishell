/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_list_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:47:25 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/23 13:27:06 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expand	*create_expand_node(t_ms *ms)
{
	t_expand	*node;

	node = malloc(1 * sizeof(t_expand));
	check_if_malloc_failed((void *)node, ms);
	node->next = NULL;
	node->str = NULL;
	return (node);
}

t_expand	*append_chunk(t_ms *ms)
{
	t_expand	*cur;

	if (ms->exp == NULL)
	{
		ms->exp = create_expand_node(ms);
		return ;
	}
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = create_expand_node(ms);
	return (cur->next);
}
