/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_lst_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:01:41 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/14 16:08:40 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

// Function to swap data of two nodes
void swapNodes(t_list *a, t_list *b) 
{
    char* temp = a->content;
    a->content = b->content;
    b->content = temp;
}

// Function to sort the list alphabetically
void sortList(t_list *head) 
{
    if (head == NULL)
        return;

    int swapped;
    t_list *ptr1;
    t_list *lptr = NULL;

    while (1) {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ft_strncmp((char *)ptr1->content, (char *)ptr1->next->content, ft_strlen((char *)ptr1->content)) > 0) {
                swapNodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;

        if (swapped == 0) {
            break;
        }
    }
}