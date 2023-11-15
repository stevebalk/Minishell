/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:16:37 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/15 14:21:44 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void prompt_handler(t_list **history_lst, t_list **env_llst, t_list **env_llst_sorted)
{
    char *prompt_in;
    int count;
    count = 0;
    
    prompt_in = NULL;
	
    if (CLR_SCREEN == 1) 
        clear_screen();

    //while((prompt_in = readline("\001\033[0;31mminihell\033[0;33m>>\033[0;36m")) != NULL)
    //while((count < 3) &&((prompt_in = readline("\001\033[0;31m\002minihell\001\033[0;33m\002>>\001\033[0;36m\002")) != NULL))
    while((prompt_in = readline("\001\033[0;31m\002minihell\001\033[0;33m\002>>\001\033[0;36m\002")) != NULL)
    {   
        //printf("has newline: %i   str >%s<\n", find_newline(prompt_in), prompt_in);
        if (ft_strlen(prompt_in) > 0)
        {
            // Adding to history llst --> todo: should be done by a function
            if (!history_lst)
                *history_lst = ft_lstnew((void*)prompt_in);
            else
                ft_lstadd_back(history_lst, ft_lstnew((void*)prompt_in));

            // 
            if (ft_strncmp(prompt_in, "exit", 4) == 0)
                break;
            
            test_parser_export(env_llst, env_llst_sorted, prompt_in);
                
            limit_history_llst(history_lst);
            write_history_llst(FILE_HISTORY, history_lst);
            add_history(prompt_in);
        }
        else
            free(prompt_in);
        count++;
    }

    c_red();printf("~prompt Handler()\n");
}
