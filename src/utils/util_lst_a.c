/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_lst_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:35:14 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/14 16:29:27 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int find_newline(char *str)
{
    int i;
    int nl;
    
    i = 0;
    nl = 0;
    
    while(str[i])
    {
        if (str[i] == '\n')
            nl = i;
        i++;
    }

    return (nl);
}

void del_first_nl(char *str)
{
    int nl_pos;
    nl_pos = find_newline(str);
    if (nl_pos > 0)
        str[nl_pos]= '\0';
} 

void	lst_delete_first(t_list **llist)
{
    if (*llist == NULL) 
        return;
    
    t_list* temp = *llist; 
    *llist = (*llist)->next; 
    free(temp->content);
    free(temp); 
}


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

void deleteList(t_list** head) 
{
    t_list *current = *head;
    t_list *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current->content); // Free the string
        free(current);       // Free the node
        current = nextNode;
    }

    *head = NULL; // Set the head to NULL
}