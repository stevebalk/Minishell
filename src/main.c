/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:12:12 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/13 11:01:13 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"



int main(void)
{
    int fd;
    fd = open("history.txt", O_RDWR | O_CREAT, 0644);
    printf("fd: %i\n", fd);

    t_list *hist_llst;
    hist_llst = NULL;
    
    load_history(fd, &hist_llst);
    show_history_list(&hist_llst);
    add_history_llst_to_prompt(&hist_llst);
    printf("history length system: %i \n", history_length);

    prompt_handler();
    
    return 0;
}
