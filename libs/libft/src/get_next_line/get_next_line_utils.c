/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:56:26 by sbalk             #+#    #+#             */
/*   Updated: 2023/08/07 13:03:31 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gnl_node_to_string(char *str, t_lst *node)
{
	size_t	i;

	i = node->start;
	while (node != NULL && node->tlen)
	{
		i = node->start;
		while (i && node->tlen)
		{
			str[node->tlen - 1] = node->str[i - 1];
			i--;
			node->tlen--;
		}
		node = node->next;
	}
}

static t_lst	*gnl_free_node(t_lst *node)
{
	t_lst	*next_node;

	next_node = node->next;
	if (node->str != NULL)
		free(node->str);
	free(node);
	return (next_node);
}

t_lst	*gnl_free_list(t_lst *node)
{
	while (node != NULL)
		node = gnl_free_node(node);
	return (NULL);
}
