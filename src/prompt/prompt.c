/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:16:37 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/10 18:20:52 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void prompt_handler(void)
{
    char *prompt_in;
    //char **history;
    
    prompt_in = NULL;
	
    //clear_screen();

    //while((prompt_in = readline("\001\033[0;31mminihell\033[0;33m>>\033[0;36m")) != NULL)
    while((prompt_in = readline("\001\033[0;31m\002minihell\001\033[0;33m\002>>\001\033[0;36m\002")) != NULL)
    {   
        if (ft_strlen(prompt_in) > 0)
            add_history(prompt_in);
        free(prompt_in);
    }
    printf("~prompt Handler()\n");
}

char *prompt_read(char *in)
{
    // c_red();printf("minihell");
    // c_yellow();printf(">>");
        
    // c_cyan();
    //in = readline("\033[0;31mminihell\033[0;33m>>\033[0;36m");
        
    //c_green();
    //printf("|%s|\n", in);

    return in;  
}	