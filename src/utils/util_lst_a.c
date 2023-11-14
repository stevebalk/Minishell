/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_lst_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:35:14 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/14 16:38:31 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

// returns the position of \n otherwise -1
int find_newline(char *str)
{
    int i;
    int nl;
    
    i = 0;
    nl = -1;
    
    while(str[i])
    {
        if (str[i] == '\n')
            nl = i;
        i++;
    }

    return (nl);
}

// replaced the first \n by \0
void del_first_nl(char *str)
{
    int nl_pos;
    nl_pos = find_newline(str);
    if (nl_pos >= 0)
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
