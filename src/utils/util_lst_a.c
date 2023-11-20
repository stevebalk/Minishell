/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_lst_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:35:14 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/20 10:47:00 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	lst_delete_first(t_list **llist)
{
	t_list	*temp;

	if (*llist == NULL)
		return ;

	temp = *llist;
	*llist = (*llist)->next;
	free(temp->content);
	free(temp);
}

// free llist and optional the content
void	lst_dealloc(t_list **llist, int free_content)
{
	t_list	*cur;
	t_list	*aux;

	cur = *llist;
	while (cur != NULL)
	{
		aux = cur;
		cur = cur->next;
		if (aux->content && free_content)
			free(aux->content);
		free(aux);
	}
	*llist = NULL;
}
