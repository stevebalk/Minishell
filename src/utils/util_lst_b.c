/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_lst_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:01:41 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/04 16:15:56 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

// copy src_llst to new_llst
void	copy_llst(t_list **src_llst, t_list **new_llst)
{
	t_list	*tmp_src;
	char	*str;

	tmp_src = *src_llst;
	if (tmp_src == NULL)
		return ;
	while (tmp_src)
	{
		str = (char *)malloc(sizeof(char)
				* (ft_strlen((char *)tmp_src->content) + 1));
		if (!str)
			return ;
		ft_strlcpy(str, (char *)tmp_src->content,
			ft_strlen((char *)tmp_src->content) + 1);
		if (!new_llst)
			*new_llst = ft_lstnew((void *)str);
		else
			ft_lstadd_back(new_llst, ft_lstnew((void *)str));
		tmp_src = tmp_src->next;
	}
}

// to swap data of two nodes
void	swap_nodes(t_list *a, t_list *b)
{
	char	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

// to sort the list alphabetically
void	sort_list(t_list *head)
{
	int		swapped;
	t_list	*ptr1;
	t_list	*lptr;

	lptr = NULL;
	if (head == NULL)
		return ;
	while (1)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
		{
			if (ft_strncmp((char *)ptr1->content, (char *)ptr1->next->content,
					ft_strlen((char *)ptr1->content)) > 0)
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
		if (swapped == 0)
			break ;
	}
}

void	delete_node_from_llst(t_list **head, t_list *node_to_delete)
{
	t_list	*temp;
	t_list	*prev;

	if (*head == NULL || node_to_delete == NULL)
		return ;
	if (*head == node_to_delete)
	{
		temp = *head;
		free(temp->content);
		*head = (*head)->next;
		free(temp);
		return ;
	}
	prev = *head;
	while (prev->next != NULL && prev->next != node_to_delete)
		prev = prev->next;
	if (prev->next == NULL)
		return ;
	temp = prev->next;
	prev->next = temp->next;
	free(temp->content);
	free(temp);
}
