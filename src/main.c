/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:12:12 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/13 15:46:32 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int main(void)
{
    t_list *hist_llst;
    hist_llst = NULL;
    
    load_history_llst(FILE_HISTORY, &hist_llst);
    limit_history_llst(&hist_llst);
    add_history_llst_to_prompt(&hist_llst);

    prompt_handler(&hist_llst);    
    
    lst_dealloc(&hist_llst);
    c_red(); printf("~main ()\n");c_reset();
    return 0;
}
