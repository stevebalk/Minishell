/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_strings_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:00:37 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/17 15:31:34 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

// returns the position of \n otherwise -1
int find_newline(char *str)
{
    int i;
    int nl;
    
    i = 0;
    nl = -1;
    
    while(str[i])
    {
        if (str[i] == '\n')
            nl = i;
        i++;
    }

    return (nl);
}

// replaced the first \n by \0
void del_first_nl(char *str)
{
    int nl_pos;
    nl_pos = find_newline(str);
    if (nl_pos >= 0)
        str[nl_pos]= '\0';
} 

char *get_string_til_first_symbol(char *str_in, char symbol)
{
	char *tmp;
	int i;

	i = 0;
	tmp = str_in;

	while(str_in[i] != symbol)
		i++;
	
	c_yellow(); printf("get_string_til_first_symbol()  str_in >%s<   symbol >%c< \n", str_in, symbol);
	printf("i: %i \n", i);
	tmp = (char*) malloc(sizeof(char) * (i + 1));
	ft_strlcpy(tmp, str_in, i + 1);
	printf("string end >%s<\n", tmp);
	return tmp;
}