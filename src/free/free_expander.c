/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:04:15 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/05 13:16:18 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Frees the given expander list and sets it to NULL */
void	free_expander_list(t_expand **list)
{
	t_expand	*cur;
	t_expand	*next;

	if (list == NULL || *list == NULL)
		return ;
	cur = *list;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->str)
			free(cur->str);
		free(cur);
		cur = next;
	}
	*list = NULL;
}
