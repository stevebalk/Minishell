/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:10:02 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/10 18:17:08 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"




void load_history(int fd)
{
    char *line;
    line = get_next_line(fd);
    
    while(line)
    {
		/*
		add history linked list
		*/
        add_history(line);
        line = get_next_line(fd);
    }
    
    if (line)
        free(line); 
}

// void write_history(t_history *history, int fd)
// {
// 	/*
// 		Todo:
// 		1. Truncate history file 
// 		2. Append every linked list line
// 	*/

	
// }