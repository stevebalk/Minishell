/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_lst_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:01:41 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/14 16:11:13 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

// copy src_llst to new_llst
void copy_llst(t_list **src_llst, t_list **new_llst)
{
    c_yellow(); printf("copy_llst()\n"); c_reset();
    t_list *tmp_src;
    tmp_src = *src_llst;
    
    if (tmp_src == NULL)
        return;
        
    while(tmp_src)
    {
        if (!new_llst)
                *new_llst = ft_lstnew(tmp_src->content);
        else
                ft_lstadd_back(new_llst, ft_lstnew(tmp_src->content));   
                  
        tmp_src = tmp_src->next;        
    }
    c_yellow(); printf("~copy_llst()\n"); c_reset();
}

// to swap data of two nodes
void swapNodes(t_list *a, t_list *b) 
{
    char* temp = a->content;
    a->content = b->content;
    b->content = temp;
}

// to sort the list alphabetically
void sortList(t_list *head) 
{
    if (head == NULL)
        return;

    int swapped;
    t_list *ptr1;
    t_list *lptr = NULL;

    while (1) 
	{
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) 
		{
            if (ft_strncmp((char *)ptr1->content, (char *)ptr1->next->content, ft_strlen((char *)ptr1->content)) > 0) {
                swapNodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;

        if (swapped == 0)
            break;
    }
}