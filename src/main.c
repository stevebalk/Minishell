/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:12:12 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/13 15:36:04 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	lst_delete_first(t_list **llist)
{
    if (*llist == NULL) 
        return;
    
    t_list* temp = *llist; 
    *llist = (*llist)->next; 
    free(temp->content);
    free(temp); 
}


void	lst_dealloc(t_list **llist)
{
	t_list	*cur;
	t_list	*aux;

	cur = *llist;
	while (cur != NULL)
	{
		aux = cur;
		cur = cur->next;
        if (aux->content)
           free(aux->content);
		free(aux);
	}
	*llist = NULL;
}

int main(void)
{
    t_list *hist_llst;
    hist_llst = NULL;
    
    load_history_llst(FILE_HISTORY, &hist_llst);
    show_history_llist(&hist_llst);
    add_history_llst_to_prompt(&hist_llst);

    prompt_handler(&hist_llst);    
    
    lst_dealloc(&hist_llst);
    c_red(); printf("~main()\n");c_reset();
    return 0;
}
