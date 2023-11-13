/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:12:12 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/13 10:50:16 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"



int main(void)
{
    int fd;
    fd = open("history.txt", O_RDWR | O_CREAT, 0644);
    printf("fd: %i\n", fd);

    t_list *history_lst;
    history_lst = NULL;
    
    load_history(fd, &history_lst);
    show_history_list(&history_lst);
    
    //prompt_handler();
    
    return 0;
}
