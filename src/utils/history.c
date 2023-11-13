/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:10:02 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/13 10:57:36 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"



void add_history_llst_to_prompt(t_list **history_lst)
{
    t_list *tmp_lst;
    tmp_lst = *history_lst;

    while(tmp_lst)
    {
        add_history((char *)tmp_lst->content);
        tmp_lst = tmp_lst->next;
    }
}

void load_history(int fd, t_list **history_lst)
{
    char *line;
    // t_list *tmp_lst;
    // tmp_lst = *history_lst;
    line = get_next_line(fd);

    while(line)
    {
		/*
		add history linked list
		*/
        if (!history_lst)
            *history_lst = ft_lstnew((void*)line);
        else
            ft_lstadd_back(history_lst, ft_lstnew((void*)line));
      
        //add_history(line);
        line = get_next_line(fd);
    }
    
    if (line)
        free(line); 
}

void show_history_list(t_list **lst)
{
    int i;
    t_list *tmp_lst;
    tmp_lst = *lst;
    
    i = 0;
    while(tmp_lst)
    {
        printf("i: %i  >", i);
        c_green();
        printf("%s", (char *)tmp_lst->content);
        c_reset();
        printf("<\n");
        tmp_lst = tmp_lst->next;
        i++;
    }
}

// void write_history(t_history *history, int fd)
// {
// 	/*
// 		Todo:
// 		1. Truncate history file 
// 		2. Append every linked list line
// 	*/

	
// }