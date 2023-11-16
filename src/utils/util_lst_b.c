/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_lst_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:01:41 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/16 13:36:37 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

// copy src_llst to new_llst
void copy_llst(t_list **src_llst, t_list **new_llst)
{
    c_yellow(); printf("copy_llst()\n"); c_reset();
    t_list *tmp_src;
	char *str;

    tmp_src = *src_llst;
    
    if (tmp_src == NULL)
        return;
        
    while(tmp_src)
    {
		str = (char *)malloc(sizeof(char) * (ft_strlen((char *)tmp_src->content) + 1));
		ft_strlcpy(str, (char *)tmp_src->content, ft_strlen((char *)tmp_src->content) + 1);
		
        if (!new_llst)
                *new_llst = ft_lstnew((void*)str);
        else
                ft_lstadd_back(new_llst, ft_lstnew((void*)str));   
                  
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

void delete_node_from_llst(t_list **head, t_list* nodeToDelete) {
    // If the linked list is empty or nodeToDelete is NULL
    if (*head == NULL || nodeToDelete == NULL) 
	{
        return;
    }

    // If the node to delete is the head node
    if (*head == nodeToDelete) 
	{
        t_list* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    // Find the previous node of the node to delete
    t_list* prev = *head;
    while (prev->next != NULL && prev->next != nodeToDelete) 
	{
        prev = prev->next;
    }

    // If the node wasn't found in the list
    if (prev->next == NULL) 
	{
        return;
    }

    // Unlink the node from the linked list and free it
    t_list* temp = prev->next;
    prev->next = temp->next;
    free(temp);
}