/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:12:12 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/14 15:59:32 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"



int	main(int argc, char **argv, char **env)
{
    t_list *hist_llst;
    t_list *env_llst;
    t_list *env_llst_sorted;
    
    hist_llst = NULL;
    env_llst = NULL;

    (void)argc;
    (void)argv;
    (void)env;

    show_env_arr(env);
    load_env_to_llst(&env_llst, env);
    show_env_llist(&env_llst);

    copy_llst(&env_llst, &env_llst_sorted);
    show_env_llist(&env_llst_sorted);

    
    //print_alphabetical(&env_llst);

    //printf("get A >%s<\n", get_alphabetical_entry(&env_llst, 'A'));
    
    // history_master(&hist_llst);
    // prompt_handler(&hist_llst);    
    
    lst_dealloc(&hist_llst);
    //lst_dealloc(&env_llst);

    c_red(); printf("~main ()\n");c_reset();
    return 0;
}
