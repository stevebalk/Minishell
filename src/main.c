/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:12:12 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/14 13:52:37 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"



int	main(int argc, char **argv, char **env)
{
    t_list *hist_llst;
    t_list *env_llst;
    
    hist_llst = NULL;
    env_llst = NULL;

    (void)argc;
    (void)argv;
    (void)env;

    show_env_arr(env);
    load_env_to_llst(&env_llst, env);
    show_env_llist(&env_llst);
    
    // history_master(&hist_llst);
    // prompt_handler(&hist_llst);    
    
    lst_dealloc(&hist_llst);
    c_red(); printf("~main ()\n");c_reset();
    return 0;
}
