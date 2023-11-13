/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:12:12 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/13 11:58:18 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"



int main(void)
{
    t_list *hist_llst;
    hist_llst = NULL;
    
    load_history_llst(FILE_HISTORY, &hist_llst);
    show_history_llist(&hist_llst);
    add_history_llst_to_prompt(&hist_llst);
    printf("history length system: %i \n", history_length);

    prompt_handler();
    
    return 0;
}
